
# Automatic Parking Barrier System with Arduino  
Ultrasonic Sensor • Servo Motor • LEDs • Push Button  

This project demonstrates a fully automated parking barrier system built using an **Arduino Uno**, **HC-SR04 ultrasonic sensor**, **SG90/SG92R servo**, **LED indicators**, and a **manual push button**.  
The barrier opens automatically when a vehicle or object is detected within range, or manually via the push button. It closes smoothly after a predefined delay.

---

## 📌 Features
- Automatic opening using **HC-SR04 ultrasonic sensor**
- Manual override using a **push button**
- Smooth servo motion (gradual opening and closing)
- Red LED → Barrier closed  
- Green LED → Barrier open  
- Adjustable:
  - Detection distance  
  - Opening duration  
  - Servo speed  
- Works with **9V battery** (servo powered through Arduino 5V)

---

## 🛠️ Components Used
- Arduino Uno  
- HC-SR04 ultrasonic sensor  
- SG90 / SG92R servo motor  
- 4-pin tactile push button  
- Red LED (closed indicator)  
- Green LED (open indicator)  
- Resistors (220Ω for LEDs)  
- Breadboard + jumper wires  
- 9V battery + connector

---

## 🔌 Wiring Diagram
You can find the following diagrams in the repository:

- **Tinkercad circuit PNG**  
- **Schematic diagram**  
- **Breadboard view**

### Key Connections
| Component | Pin |
|----------|-----|
| HC-SR04 Trig | D2 |
| HC-SR04 Echo | D3 |
| Servo Signal | D9 |
| Red LED | D4 |
| Green LED | D5 |
| Push Button | D6 (INPUT_PULLUP) |
| All Grounds | Common GND |

---

## 💻 Arduino Code
The complete code is available in the `parking_barrier.ino` file.  
It includes:
- Debounced button input  
- Smooth servo motion  
- Adjustable settings  
- Ultrasonic distance detection  

---

## 🚀 How It Works
1. The ultrasonic sensor continuously measures distance.  
2. If an object is detected within the set threshold, the barrier **automatically opens**.  
3. Alternatively, the user can press the button to manually open the barrier.  
4. The green LED lights up while the barrier is open.  
5. After the timer expires, the barrier **slowly returns to the closed position**, and the red LED turns on.  
6. Any new trigger resets the timer.

---

## 📷 Images Included
- Tinkercad circuit drawing (PNG)  
- Schematic view  
- Breadboard connection diagram  

---

## 🧪 Testing
- Open Serial Monitor at 9600 baud to view sensor readings.  
- Adjust distance threshold if needed (default: 15 cm).  
- Servo speed and open duration can be changed in the code:
  ```cpp
  const int servoSpeed = 2;
  const unsigned long openDuration = 4000;

---

🔧 Customization Ideas

You can expand the project with:

Bluetooth control (HC-05)

IR remote control

OLED/LCD screen

Buzzer for warning

Automatic night lighting



---

📄 License

This project is released under the MIT License.
You may copy, modify, and use it freely.


---

🙌 Credits

Created by Mutlu Ergöz
Tinkercad design, Arduino wiring, and full implementation by the author.