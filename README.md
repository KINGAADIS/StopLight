# StopLight

# 🚦 Traffic Light Controller with TFT Display  
_A microcontroller-based traffic light simulation using MPLAB X and PIC18F4620_

## 📌 Project Overview
This project implements a state-based traffic light controller for a 4-way intersection using a PIC18F4620 microcontroller. It simulates not only standard green/yellow/red transitions but also integrates pedestrian crosswalk controls, left-turn signaling, night mode, a TFT full-color display, and audible alerts — making it a rich embedded systems learning experience.

<img src="docs/demo.jpg" width="400">

---

## 🛠️ Features
- **Day/Night Mode**: Automatically switches modes using a light sensor (ADC).
- **Interrupt-Driven Inputs**:
  - Pedestrian buttons (north-south and east-west)
  - Left turn signal requests
  - Emergency flashing override
- **Full Graphics LCD Display**:  
  Visualizes the current state of lights, countdown timers, switch states, and system mode on an ST7735 TFT display.
- **Buzzer Audio Alerts**:  
  Beeps during pedestrian countdowns and while transitioning states.
- **Flashing Mode**:  
  All signals alternately flash for emergency or servicing mode (activated via interrupt).

---

## 🧱 Hardware Requirements
- **Microcontroller**: PIC18F4620
- **Display**: ST7735 TFT with SPI interface
- **Inputs**: Push-buttons for pedestrians & left-turn requests; light sensor (potentiometer or LDR)
- **Outputs**: LEDs or LED arrays representing signaling lights, buzzer for sound
- Breadboard, jumper wires, resistors, and USB programmer (e.g., PICkit)

---

## 🗂️ Project Structure
