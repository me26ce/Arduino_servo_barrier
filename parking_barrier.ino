// The code includes:

// - Ultrasonic distance measurement  
// - Button debouncing  
// - Smooth servo motion  
// - Adjustable timer and servo speed
// - LED indicators  



// ## 🚀 How It Works

// 1. The ultrasonic sensor continuously measures distance.  
// 2. If a vehicle/object is detected within a defined threshold, the barrier opens.  
// 3. The push button can also open the barrier manually.  
// 4. Barrier stays open for a configurable duration.  
// 5. Servo slowly closes the barrier.  
// 6. New triggers reset the timer.



// ⚙️ Customization

// You can enhance this project by adding:

// - OLED display for status  
// - Bluetooth remote control (HC-05)  
// - Buzzer warning  
// - Auto night LED system  
// - WiFi control with ESP8266  



// 📄 License

// This project is licensed under the **MIT License**.  
// See the `LICENSE` file for details.



// 🙌 Credits

// Project developed by **Mutlu Ergöz**  
// Tinkercad modeling, wiring, and programming by the author.

// ⭐ If you like this project, feel free to star the repository!

  #include <Servo.h>

Servo bariyer;

// PIN TANIMLARI
const int trigPin = 7;
const int echoPin = 6;
const int servoPin = 9;
const int ledRed = 3;
const int ledGreen = 4;
const int buttonPin = 5;

// AYARLAR
const unsigned long openDuration = 4000UL; // açık kalma süresi (ms)
const int distanceThreshold = 15; // cm — araç 15 cm'den yakında olursa bariyer açılır

// DEĞİŞKENLER
unsigned long openUntil = 0;
bool isOpen = false;

// Buton debouncing
int lastButtonReading = HIGH;
int buttonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

// Servo kontrol
int servoClosedPos = 0;
int servoOpenPos = 90;
int currentPos = 0;
int targetPos = 0;
const int servoSpeed = 2;     // daha büyük = daha hızlı hareket
unsigned long lastMoveTime = 0;
const unsigned long moveInterval = 15;

void setup() {
  Serial.begin(9600);

  bariyer.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);

  currentPos = servoClosedPos;
  targetPos = servoClosedPos;
  bariyer.write(currentPos);
  digitalWrite(ledRed, HIGH);
  digitalWrite(ledGreen, LOW);
}

// Mesafe ölçüm fonksiyonu
long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 25000); // 25 ms timeout (~4m)
  long distance = duration * 0.034 / 2;          // cm’ye çevir
  return distance;
}

void loop() {
  unsigned long now = millis();

  // --- MESAFE OKUMA ---
  long distance = measureDistance();
  Serial.print("Mesafe: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance < distanceThreshold) {
    openUntil = now + openDuration;
    if (!isOpen) {
      Serial.println("Araç algılandı, bariyer açılıyor...");
      targetPos = servoOpenPos;
      digitalWrite(ledRed, LOW);
      digitalWrite(ledGreen, HIGH);
      isOpen = true;
    }
  }

  // --- BUTON OKUMA ---
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonReading) {
    lastDebounceTime = now;
  }
  if ((now - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        Serial.println("Buton basıldı, bariyer açılıyor...");
        openUntil = now + openDuration;
        if (!isOpen) {
          targetPos = servoOpenPos;
          digitalWrite(ledRed, LOW);
          digitalWrite(ledGreen, HIGH);
          isOpen = true;
        }
      }
    }
  }
  lastButtonReading = reading;

  // --- SÜRE DOLUNCA KAPAT ---
  if (isOpen && now >= openUntil) {
    Serial.println("Süre doldu, bariyer kapanıyor...");
    targetPos = servoClosedPos;
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    isOpen = false;
  }

  // --- SERVO'YU YAVAŞ HAREKET ETTİR ---
  if (now - lastMoveTime >= moveInterval) {
    lastMoveTime = now;
    if (currentPos < targetPos) {
      currentPos += servoSpeed;
      if (currentPos > targetPos) currentPos = targetPos;
      bariyer.write(currentPos);
    } else if (currentPos > targetPos) {
      currentPos -= servoSpeed;
      if (currentPos < targetPos) currentPos = targetPos;
      bariyer.write(currentPos);
    }
  }

  delay(50);
}
