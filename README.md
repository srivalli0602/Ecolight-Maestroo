# 🌃 Ecolight Maestro

### Time & Light Intensity Based Street Light Automation using LPC2129 ARM7


![Microcontroller](https://img.shields.io/badge/LPC2129-ARM7-success)
![Language](https://img.shields.io/badge/Language-Embedded%20C-orange)
![IDE](https://img.shields.io/badge/Keil-uVision-red)
![Simulation](https://img.shields.io/badge/Proteus-Simulation-yellow)

---

## 📖 Project Overview

**Ecolight Maestro** is an intelligent street light automation system developed using the **LPC2129 ARM7 Microcontroller**. The system automatically controls street lights based on **real-time clock scheduling** and **ambient light intensity detection** using an LDR sensor.

Traditional street lighting systems often remain ON unnecessarily, leading to excessive energy consumption. This project addresses that issue by combining **time-based automation** with **light intensity monitoring**, ensuring that street lights operate only when required.

The system continuously monitors:

* Current Time and Date using RTC
* Ambient Light Intensity using LDR and ADC
* User-configurable RTC parameters through Keypad Interface

This results in an energy-efficient and fully automated smart lighting solution.

---

## 🎯 Project Objectives

✔ Reduce power wastage in street lighting systems

✔ Automate street light operation based on environmental conditions

✔ Provide user-friendly RTC configuration

✔ Demonstrate ARM7 peripheral integration

✔ Implement interrupt-driven embedded system design

---

## ✨ Key Features

### 🕒 Real-Time Clock Management

* Displays current Time
* Displays Date
* Displays Day
* Supports RTC parameter modification

### 🌞 Intelligent Light Detection

* LDR-based ambient light sensing
* ADC conversion for light intensity measurement
* Automatic day/night detection

### 💡 Automatic Street Light Control

* Lights turn ON during low-light conditions
* Lights turn OFF during daylight conditions
* Dual-condition verification using RTC and LDR

### ⌨ User Configuration Interface

* 4x4 Matrix Keypad
* RTC parameter editing
* Menu-driven operation

### ⚡ Interrupt Driven Design

* EINT0 external interrupt support
* Instant access to RTC configuration menu
* Responsive user interaction

### 📟 LCD Monitoring

Displays:

* Time
* Date
* Day
* ADC Value
* Menu Options
* System Status

---

# 🏗 System Architecture

```text
                 +----------------+
                 |     RTC        |
                 +--------+-------+
                          |
                          v
+---------+      +--------------------+
|  Keypad |----->|     LPC2129        |
+---------+      |                    |
                 |                    |
                 |  Decision Logic    |
                 |                    |
+---------+      |                    |
|   LDR   |----->| ADC Conversion     |
+---------+      +---------+----------+
                           |
                           v
                   +---------------+
                   |     LEDs      |
                   | Street Lights |
                   +---------------+

                           ^
                           |
                     +-----------+
                     | LCD 16x2  |
                     +-----------+
```

---

# ⚙ Working Principle

The system continuously performs the following operations:

### Step 1

Initialize:

* LCD
* RTC
* ADC
* GPIO
* Interrupts

### Step 2

Read current:

* Hour
* Minute
* Second
* Date
* Day

from RTC.

### Step 3

Read LDR value through ADC.

### Step 4

Determine whether the environment is:

* Daytime
* Nighttime

based on RTC and light intensity.

### Step 5

Control street lights automatically.

### Step 6

Monitor external interrupt (EINT0).

When interrupt occurs:

* Open RTC configuration menu
* Allow parameter modification
* Save updated values
* Resume normal operation

---

# 💡 Street Light Decision Logic

## LED OFF Condition

```text
Time < 18:00
OR
ADC Value > 300
```

### Example

```text
Time = 14:00:00
ADC  = 550

Result:
LED OFF
```

---

## LED ON Condition

```text
Time >= 18:00
AND
ADC Value < 300
```

### Example

```text
Time = 19:30:00
ADC  = 120

Result:
LED ON
```

---

# 🔄 System Flow

```text
                 START
                    |
                    v
          Initialize LCD
                    |
                    v
          Initialize RTC
                    |
                    v
          Initialize ADC
                    |
                    v
            Read Time
                    |
                    v
            Read LDR
                    |
                    v
      Time >= 6 PM AND
       ADC < Threshold ?
            /        \
          YES        NO
           |          |
           v          v
      LED ON      LED OFF
           |
           v
      Interrupt ?
           |
      +----+----+
      |         |
     NO        YES
      |         |
      |    Open RTC Menu
      |         |
      +---------+
           |
           v
        Repeat
```

---

# ⌨ RTC Configuration Menu

The RTC settings can be modified using the keypad whenever EINT0 is triggered.

### Interrupt Pin

```text
EINT0 → P0.16
```

### Menu Options

```text
1 → Update Hour

2 → Update Minute

3 → Update Second

4 → Update Day

5 → Update Date

6 → Update Month

7 → Update Year

8 → Exit Menu
```

---

# 🛠 Hardware Components

| Component        | Purpose                     |
| ---------------- | --------------------------- |
| LPC2129 ARM7 MCU | Main Controller             |
| LCD 16x2         | User Interface              |
| LDR Sensor       | Light Detection             |
| ADC Channel      | Sensor Data Acquisition     |
| RTC Module       | Time Management             |
| 4x4 Keypad       | User Input                  |
| LEDs             | Street Light Simulation     |
| Push Button      | EINT0 Interrupt Trigger     |
| Resistors        | Current Limiting & Pull-ups |

---

# 💻 Software Tools

| Tool         | Usage                |
| ------------ | -------------------- |
| Keil uVision | Firmware Development |
| Embedded C   | Programming          |
| Proteus      | Circuit Simulation   |
| Flash Magic  | Programming LPC2129  |
| Git          | Version Control      |
| GitHub       | Project Hosting      |

---

# 🧠 LPC2129 Peripherals Utilized

### GPIO

* LED Control
* LCD Interface
* Keypad Interface

### ADC

* LDR Sensor Reading
* Ambient Light Measurement

### RTC

* Real-Time Tracking
* Date and Time Management

### External Interrupt (EINT0)

* Menu Activation
* User Interaction

---

# 📂 Project Structure

```text
Ecolight-Maestro
│
├── src
│   ├── MINI.c
│   ├── ADC.c
│   ├── KPM2.c
│   ├── RTC_Main.c
│   ├── LCD.c
│   └── delayms.c
│
├── inc
│   ├── ADC.h
│   ├── ADC_defines.h
│   ├── delaydef.h
│   ├── kpm_defines.h
│   └── lcd.h
│
├── simulation
│   ├── Project.pdsprj
│   ├── HEX File
│   └── Circuit Files
│
├── media
│   ├── Demo.mp4
|   |__ Circuit Connection.png
│   └── Project_Image.png
│
└── README.md
```

---

# 🚀 Future Enhancements

* Wireless Monitoring using IoT
* GSM-Based Fault Reporting
* Solar Powered Street Lights
* Motion Detection for Adaptive Brightness
* Cloud-Based Energy Analytics
* Mobile Application Integration

---

# 🎓 Learning Outcomes

Through this project, I gained practical experience in:

* ARM7 LPC2129 Programming
* Embedded C Development
* RTC Programming
* ADC Interfacing
* Sensor Integration
* Interrupt Handling
* Keypad Interfacing
* LCD Interfacing
* Embedded System Design
* Power Efficient Automation Techniques

---


## ✨ Creator

**Srivalli Gandham**  
ARM7 • Embedded C • Firmware Development • Embedded Systems

*Turning ideas into embedded solutions through code and hardware.*

## ⭐ If you found this project useful, consider giving it a Star on GitHub!
