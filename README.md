# Ecolight Maestro - Smart Street Light Automation using LPC2148

## Project Overview

Ecolight Maestro is an embedded mini project developed using **LPC2129 ARM7 microcontroller**.  
The system performs automatic street light control based on:

- Real Time Clock (RTC)
- LDR sensor using ADC
- Automatic LED control
- RTC parameter editing through keypad
- External interrupt based menu access

The project reduces unnecessary power consumption by turning ON/OFF street lights according to time and ambient light intensity.

---

## Features

✅ Real time clock display

✅ Date and day display

✅ Automatic light control using LDR

✅ RTC edit menu

- Hour update
- Minute update
- Second update
- Day update
- Date update
- Month update
- Year update

✅ Keypad interface

✅ LCD display

✅ EINT0 interrupt support

---

## Working Principle

System continuously displays:

- Time
- Date
- Day
- ADC value

Street light operation condition:

### LED OFF Condition

LEDs remain OFF when:

```text
Time < 6 PM
OR
LDR ADC value > 300
```

### LED ON Condition

LEDs turn ON when:

```text
Time >= 6 PM
AND
ADC value < 300
```

Example:

```text
Time : 19:30:00
ADC  : 120

Result:
LED = ON
```

Example:

```text
Time : 14:00:00

Result:
LED = OFF
```

---

## Hardware Components

| Component | Description |
|-----------|------------|
| LPC2129 | ARM7 Microcontroller |
| LCD 16x2 | Display time and menu |
| LDR | Light sensing |
| ADC Channel 0 | Reads LDR value |
| RTC | Time management |
| Keypad 4x4 | Menu input |
| LEDs | Street lights |
| Push Button | EINT0 interrupt trigger |
| Resistors | Pull up / current limiting |

---

## Software Tools

- Keil uVision
- Proteus
- Embedded C
- Flash Magic
- Git
- GitHub

---

## Tech Stack

### Hardware

- LPC2148 ARM7
- RTC Module
- LDR Sensor
- LEDs
- Keypad
- LCD

### Software

- Embedded C
- Keil IDE
- Proteus Simulation
- GitHub Version Control

---

## Folder Structure

```text
Ecolight-Maestro/
│
├── src/
│   ├── MINI.c
│   ├── ADC.c
│   ├── KPM2.c
│   ├── RTC_Main.c
│   ├── LCD.c
│   └── delayms.c
│
├── inc/
│   ├── ADC.h
│   ├── ADC_defines.h
│   ├── delaydef.h
│   ├── kpm_defines.h
│   └── lcd.h
│
├── simulation/
│   ├── Project.pdsprj
│   ├── HEX File
│   └── Circuit Files
│
├── media/
│   ├── Demo.mp4
│   └── Project_Image.png
│
└── README.md
```
## Interrupt Operation

Push switch connected to:

```text
EINT0 → P0.16
```

Interrupt opens RTC edit menu.

User can modify:

```text
1 → Hour
2 → Minute
3 → Second
4 → Day
5 → Date
6 → Month
7 → Year
8 → Exit
```

---

## Project Flow

```text
Start
   ↓
Initialize LCD
   ↓
Initialize RTC
   ↓
Initialize ADC
   ↓
Read Time
   ↓
Check Day/Night
   ↓
Read LDR
   ↓
Control LEDs
   ↓
Interrupt?
   ↓
Open RTC Menu
   ↓
Update Parameters
   ↓
Return
```

---


## Author

Srivalli Gandham

Embedded Systems | ARM | LPC2129 | Embedded C
