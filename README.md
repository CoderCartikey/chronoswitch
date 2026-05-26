# ⏰ ChronoSwitch V1

> An automated exoskeleton for your wall switch — built by a renter who couldn't touch the wiring.

---

## 🧠 The Problem

I live in a rented hostel room. No wiring changes allowed. No smart bulbs. No budget for expensive smart plugs.

So I built a physical solution: a device that **sits on top of the existing switch** and flips it at a programmed time — no modifications to the room required.

---

## ⚙️ How It Works

An **Arduino Nano** reads the current time from a **DS3231 RTC module**. When the clock matches a preset wake or sleep time, it triggers an **SG90 servo** to physically press the switch — then returns to rest position.

Two alarms are supported out of the box:
- **WAKE** — turns the light ON at a set time
- **SLEEP** — turns it OFF at a set time

---

## 🛠️ Hardware

| Component       | Details                        |
|----------------|--------------------------------|
| Microcontroller | Arduino Nano                   |
| RTC Module      | DS3231 (I2C)                   |
| Actuator        | SG90 Servo Motor               |
| Power           | AC adapter (5V)                |
| Frame           | Hand-built, taped to wall      |

**Wiring:**
- Servo signal → Pin 9
- DS3231 → SDA (A4), SCL (A5)
- Both powered via Arduino 5V/3.3V rails

---

## 💻 Software

- Language: C++ (Arduino IDE)
- Libraries: `RTClib`, `Servo`, `Wire`

**To configure your own times**, edit these lines in the code:

```cpp
#define WAKE_HOUR     7
#define WAKE_MINUTE   10

#define SLEEP_HOUR    23
#define SLEEP_MINUTE  0
```

**To adjust servo travel** (based on your switch stiffness):

```cpp
#define SERVO_REST      120   // resting angle
#define SERVO_PUSH      20    // push angle
#define PUSH_DURATION   2000  // ms to hold
```

> ⚠️ **Time Sync Note:** On upload, the RTC auto-syncs with your laptop's compile-time clock. If you re-upload without changing the code, time will reset — comment out the `rtc.adjust(...)` line after first upload.

---

## 📦 Installation

1. Install libraries via Arduino IDE Library Manager:
   - `RTClib` by Adafruit
   - `Servo` (built-in)
2. Open `ChronoSwitch_v1.ino`
3. Set your desired times in the `#define` section
4. Upload — RTC syncs automatically on first flash
5. Comment out `rtc.adjust(...)` and re-upload to lock the time

---

## 🏗️ Build Constraints (The Real Story)

- No lab, no soldering iron, broken breadboard
- Hand-peeled wires, friction-fit connections
- Frame designed via 2D sketches for low center of gravity
- Light enough to stay on the wall with cello tape
- 13 days of iteration and debugging in a hostel room

**Total cost: ~₹826**

---

## 📁 Repository Structure

```
chronoswitch/
├── ChronoSwitch_v1/
│   └── ChronoSwitch_v1.ino
└── README.md
```

---
<img width="4096" height="3072" alt="IMG20260522045831" src="https://github.com/user-attachments/assets/72943c83-4745-4ffe-a7f6-23cac532c40a" />
<img width="6144" height="6144" alt="IMG_20260522_050523" src="https://github.com/user-attachments/assets/7dbe3226-52a3-4a12-a2f0-7416f7faa7f9" />
<img width="3072" height="4096" alt="IMG20260522051031" src="https://github.com/user-attachments/assets/98fb2a19-e338-4f98-8091-a56075e9859a" />

## 👤 Author
B.Tech CSE, DIT University, Dehradun

---

*Built out of necessity. Refined out of stubbornness.*


