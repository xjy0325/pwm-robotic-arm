# PWM Robotic Arm Control

## Description
An embedded C project on an AVR microcontroller that drives a robotic arm using PWM signals. The system also reads analog input via ADC, displays information on an SSD1306 OLED screen, and communicates over I2C and UART.

## Features
- Generates PWM signals with hardware timers to control servo motors
- Reads analog input through the ADC
- Displays status on an SSD1306 OLED via I2C
- UART communication for debugging and control
- Written in pure C using direct register access (no Arduino library)

## Hardware
- AVR microcontroller (ATmega2560)
- Robotic arm with servo motors
- SSD1306 OLED display
- Analog input source (e.g. potentiometer)

## How to Build
1. Open `ADCdemo.cproj` in Microchip Studio (or Atmel Studio 7).
2. Build the project and flash it to the AVR microcontroller.
3. Power the robotic arm and observe the PWM-controlled motion.

> Note: The project uses direct register access, so it targets the specific
> AVR MCU configured in the project file.

## Demo
[https://www.youtube.com/watch?v=CmyP_95AZYM]

## Concepts
- PWM generation with hardware timers
- ADC (analog-to-digital conversion)
- I2C and UART communication
- OLED display driver (SSD1306)
- Bare-metal C programming on AVR

## Project Structure
- `src/` — source code (main, timer/PWM, ADC, I2C, UART, OLED)
- `docs/Robot Arm Report.pdf` — full project report
- `ADCdemo.cproj` — Microchip Studio project file

## Files
- `src/main.c` — main program
- `src/timer.c` / `src/timer.h` — timer and PWM logic
- `src/initADC.c` / `src/initADC.h` — ADC initialization
- `src/I2C.c` / `src/I2C.h` — I2C communication
- `src/UART0.c` / `src/UART0.h` — UART communication
- `src/ssd1306.c` / `src/ssd1306.h` — OLED display driver
- `src/data.h` — shared data
- `docs/Robot Arm Report.pdf` — project report
- `ADCdemo.cproj` — Microchip Studio project