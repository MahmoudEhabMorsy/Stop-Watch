# AVR Stop Watch System

> **Educational Project Notice**
> This project was developed as an educational embedded systems application using AVR microcontrollers and low-level embedded C programming. The system demonstrates timer configuration, interrupt handling, multiplexed seven-segment display control, and real-time stopwatch functionality.

## Overview

The AVR Stop Watch System is a real-time embedded stopwatch application implemented using an AVR microcontroller.

The project uses:

* Timer1 in CTC mode
* External interrupts
* Multiplexed seven-segment displays
* GPIO register-level programming
* Interrupt Service Routines (ISR)

The stopwatch displays:

```text
HH:MM:SS
```

using six multiplexed seven-segment displays.

The system supports:

* Start functionality
* Stop functionality
* Reset functionality
* Real-time time counting

The project was implemented in Embedded C using direct AVR register manipulation.

---

# Features

* Real-time stopwatch counting
* Hours, minutes, and seconds display
* Multiplexed seven-segment display control
* Timer1 CTC mode configuration
* External interrupt handling
* Start/Stop/Reset control
* Register-level AVR programming
* Interrupt-driven timing system
* Embedded real-time behavior

---

# Technologies Used

* Embedded C
* AVR Microcontroller Programming
* Timer1 CTC Mode
* Interrupt Service Routines (ISR)
* GPIO Programming
* Seven-Segment Display Interfacing
* Eclipse CDT
* AVR-GCC

---

# Hardware Components

The project was designed using:

* AVR Microcontroller
* Six Seven-Segment Displays
* Push Buttons
* External Interrupt Pins
* Crystal Oscillator / Internal Clock
* Breadboard and Embedded Circuit Components

---

# System Architecture

The stopwatch system is divided into several functional modules:

| Module                | Responsibility                              |
| --------------------- | ------------------------------------------- |
| Timer Module          | Generates periodic timing interrupts        |
| Interrupt Module      | Handles external interrupt events           |
| Display Module        | Controls multiplexed seven-segment displays |
| Time Management Logic | Updates seconds, minutes, and hours         |
| GPIO Configuration    | Initializes AVR pins and peripherals        |

---

# Project Structure

```text
Stop-Watch-main/
│
├── Stop_Watch/
│   ├── Stop_watch.c
│   ├── .project
│   ├── .cproject
│   └── .settings/
│
└── .metadata/
```

---

# Stopwatch Functionality

The stopwatch tracks:

```text
Seconds → Minutes → Hours
```

using a time array:

```c
unsigned char Time_array[6] = { 0 };
```

Array layout:

| Index | Purpose       |
| ----- | ------------- |
| 0     | Seconds Units |
| 1     | Seconds Tens  |
| 2     | Minutes Units |
| 3     | Minutes Tens  |
| 4     | Hours Units   |
| 5     | Hours Tens    |

---

# Timer Configuration

The project uses:

```text
Timer1 in CTC Mode
```

for accurate time generation.

### Timer Features

| Parameter        | Value                   |
| ---------------- | ----------------------- |
| Timer            | Timer1                  |
| Mode             | CTC Mode                |
| Prescaler        | 1024                    |
| Compare Register | OCR1A                   |
| Interrupt Type   | Compare Match Interrupt |

Example configuration:

```c
OCR1A = 977;
```

---

# Interrupt Handling

The system relies heavily on interrupts for real-time behavior.

## Timer Interrupt

The timer compare interrupt increments the stopwatch every second.

Example ISR:

```c
ISR(TIMER1_COMPA_vect)
```

---

## External Interrupts

The project uses external interrupts for user control.

| Interrupt | Function         |
| --------- | ---------------- |
| INT0      | Reset Stopwatch  |
| INT1      | Stop Stopwatch   |
| INT2      | Resume Stopwatch |

Example ISR:

```c
ISR(INT0_vect)
ISR(INT1_vect)
ISR(INT2_vect)
```

---

# Multiplexed Seven-Segment Display

The stopwatch uses multiplexing to control six seven-segment displays efficiently.

### Multiplexing Process

The system:

1. Enables one display at a time
2. Sends digit data
3. Quickly switches to the next display
4. Repeats continuously

This creates the illusion that all displays are active simultaneously.

Example display logic:

```c
PORTA = (PORTA & 0xC0) | 0x01;
PORTC = (PORTC & 0xF0) | Time_array[0];
```

---

# GPIO Configuration

The project directly manipulates AVR registers such as:

```c
DDRA
DDRC
PORTA
PORTC
```

This approach provides:

* High execution speed
* Full hardware control
* Low-level embedded programming experience
* Minimal abstraction overhead

---

# Core Embedded Concepts Demonstrated

This project demonstrates several important embedded systems concepts:

* Timer configuration
* Interrupt-driven programming
* Multiplexed display control
* Real-time embedded systems
* GPIO register programming
* State management
* Delay timing
* Embedded hardware interfacing

---

# Program Workflow

```text
Initialize GPIO Pins
          ↓
Initialize Timer1
          ↓
Initialize External Interrupts
          ↓
Enable Global Interrupts
          ↓
Wait for Timer Interrupt
          ↓
Update Stopwatch Time
          ↓
Refresh Seven-Segment Displays
```

---

# Development Environment

The project was developed using:

* Eclipse CDT
* AVR-GCC Compiler
* Embedded C

Included libraries:

```c
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
```

---

# How to Build and Run

## 1. Clone the Repository

```bash
git clone https://github.com/MahmoudEhabMorsy/Stop-Watch.git
```

## 2. Open the Project

Import the project into:

* Eclipse CDT
* Atmel Studio
* Microchip Studio

## 3. Compile the Project

Using AVR-GCC:

```bash
avr-gcc Stop_watch.c -o stopwatch.elf
```

## 4. Flash to AVR Microcontroller

Upload the generated firmware using:

* USBasp
* AVRDUDE
* Atmel Programmer

## 5. Connect Hardware

Ensure proper connection of:

* Seven-segment displays
* Push buttons
* AVR microcontroller pins

---

# Example Functional Behavior

## Stopwatch Running

```text
00:00:01
00:00:02
00:00:03
```

## Reset Button Pressed

```text
00:00:00
```

## Stop Button Pressed

Timer pauses.

## Resume Button Pressed

Timer resumes counting.

---

# Educational Value

This project is highly valuable for learning:

* Embedded systems fundamentals
* AVR microcontroller programming
* Timer modules
* External interrupts
* Real-time applications
* Display interfacing
* Low-level hardware control

It serves as a strong practical introduction to:

* Embedded firmware development
* Real-time embedded systems
* Hardware/software integration

---

# Possible Future Improvements

Potential enhancements include:

* LCD or OLED display integration
* Lap timing functionality
* EEPROM time storage
* Buzzer alarm support
* RTC module integration
* Low-power sleep modes
* RTOS integration
* Adjustable stopwatch precision
* Start/Stop debounce handling
* Wireless synchronization

---

# Known Limitations

* Software delay-based multiplexing
* No hardware debounce handling
* Limited UI functionality
* Prototype educational implementation
* No persistent time storage

---

# Software Design Highlights

The project emphasizes:

* Register-level embedded programming
* Clean interrupt-driven architecture
* Efficient multiplexing logic
* Real-time responsiveness
* Low-level hardware interaction

---

# Author

Developed by:

* Mahmoud Ehab

---

# License

This project is provided for educational and learning purposes.

You are free to study, modify, and extend the implementation for academic or personal use.

---

# Acknowledgments

Special thanks to:

* AVR embedded systems documentation
* Embedded systems learning communities
* Open-source AVR programming resources
* Educational firmware development references
