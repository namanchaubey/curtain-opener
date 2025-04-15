# Curtain-opener
# LPC1768 Stepper Motor Controller

This project demonstrates how to control a stepper motor using the **LPC1768 ARM Cortex-M3 microcontroller**. It integrates keypad input, LCD display, GPIO control, and hardware timers to perform directional control (clockwise/anti-clockwise) and timed operation of a stepper motor.

---

## 📌 Features

- ⌨️ **4x4 Matrix Keypad Interface**:  
  Users can input commands using keys (e.g., `B` for direction control, `T` for timed operation).

- ⏱️ **Timer0-Based Delays**:  
  Uses hardware timer for accurate delays and match interrupts.

- 🧭 **Stepper Motor Direction Control**:  
  - Clockwise rotation on Switch input high (`P2.12`)
  - Anticlockwise rotation on Switch input low

- 🖥️ **LCD Display Interface**:  
  Display messages and prompt for time input via keypad.

---

## 🔋 How It Works

- On boot, waits for keypad input:
  - Press `B` → Enters continuous switch mode: rotates motor clockwise or counterclockwise based on input pin `P2.12`.
  - Press `T` → Prompts user to enter a number (0–9) via keypad. That number is multiplied by 1 hour and used as a timer duration for stepper rotation.
  
- The stepper motor is rotated by shifting bits on GPIO port pins connected to its coils.

---

## 🧩 Hardware Requirements

- LPC1768 Microcontroller Board
- 4x4 Matrix Keypad
- Stepper Motor (e.g., 28BYJ-48)
- ULN2003 or L293D Motor Driver
- LCD Display (16x2)
- Push Button (optional for testing)
- Power Supply

---

## 📁 File Structure

