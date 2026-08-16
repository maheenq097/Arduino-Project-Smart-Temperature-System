# Temperature-Based LED & Fan Indicator System

An Arduino-based project that monitors ambient temperature and provides visual (LED) and mechanical (fan/motor) feedback based on temperature thresholds. Built and simulated with a TMP36 sensor and DC motor, and implemented physically with a DHT11 sensor and a 28BYJ-48 stepper motor (with ULN2003 driver).

---

## Overview

This project reads the ambient temperature and reacts as follows:

| Condition | LED | Fan/Motor |
|---|---|---|
| Temp > 35°C | Red LED ON | Fan/motor runs |
| 25°C ≤ Temp ≤ 35°C | Yellow LED ON | Off |
| Temp < 25°C | Blue LED ON | Off |

The project was designed in two stages:
1. **Simulation stage** — built and tested on an online circuit simulator (Tinkercad) using a **TMP36 analog temperature sensor** and a **DC motor** (with NPN transistor + flyback diode as a fan substitute).
2. **Physical build stage** — implemented in real hardware using a **DHT11 digital temperature sensor** and a **28BYJ-48 stepper motor** driven through a **ULN2003 driver board**, since a DC fan/motor wasn't available in hardware.

Both versions are functionally equivalent — the sensor and motor code sections are interchangeable depending on what components are available.

---

## Components Used

### Simulation version (TMP36 + DC motor)
- Arduino Uno
- TMP36 analog temperature sensor
- 3x LED (red, yellow, blue)
- 3x 220Ω resistor (LED current limiting)
- DC motor (fan substitute)
- NPN transistor (e.g. 2N2222/BC547) — motor switch
- 1x 1kΩ resistor (transistor base)
- 1x flyback diode (across motor terminals, protects transistor from voltage spikes)
- 9V battery / external power supply
- Breadboard + jumper wires

### Real hardware version (DHT11 + stepper motor)
- Arduino Uno
- DHT11 digital temperature sensor
- 3x LED (red, yellow, blue)
- 3x 220Ω resistor (LED current limiting)
- 28BYJ-48 stepper motor
- ULN2003 stepper driver board
- Breadboard + jumper wires

---

## Circuit Diagram Notes

### TMP36 + DC motor (simulation)
- TMP36: flat side facing you, pins left to right = VCC → OUT (to A0) → GND
- LEDs: each through a 220Ω resistor to GND, driven by digital pins
- DC motor circuit (transistor switch):
  - Arduino signal pin → 1kΩ resistor → transistor **base**
  - Motor **negative** terminal → transistor **collector**
  - Transistor **emitter** → GND
  - Motor **positive** terminal → external power supply (+)
  - Flyback diode placed **directly across the motor's two terminals**, banded (cathode) end facing the positive side — protects the transistor from voltage spikes when the motor switches off

### DHT11 + stepper motor (real hardware)
- DHT11: VCC → 5V, GND → GND, DATA → digital pin 7 (add 10kΩ pull-up between DATA and VCC if not built into the module)
- LEDs: same as above, each through 220Ω resistor to GND
- Stepper motor:
  - Motor's ribbon connector plugs directly into the ULN2003 board
  - ULN2003 IN1–IN4 → Arduino digital pins 8, 9, 10, 11
  - ULN2003 power (+/−) → 5V supply
  - Arduino GND, ULN2003 GND, and external supply GND must all be tied to a common ground

---

## Pin Mapping

| Component | Arduino Pin |
|---|---|
| TMP36 signal (simulation) | A0 |
| DHT11 data (real hardware) | 7 |
| Red LED | 2 |
| Yellow LED | 3 |
| Blue LED | 4 |
| DC motor / transistor base (simulation) | 7 |
| ULN2003 IN1 (real hardware) | 8 |
| ULN2003 IN2 (real hardware) | 9 |
| ULN2003 IN3 (real hardware) | 10 |
| ULN2003 IN4 (real hardware) | 11 |

Note: In the simulation version, the motor's transistor base signal used pin 7, which is also used for DHT11 data in the real version. When switching between versions, only one of the two (TMP36+DC motor OR DHT11+stepper) is active at a time, so there's no actual pin conflict.

---

## Libraries Required

- **DHT sensor library** by Adafruit (for DHT11 version)
- **Adafruit Unified Sensor** (dependency of the above)
- **Stepper.h** (built into Arduino IDE, no separate install needed)

Install via Arduino IDE: `Sketch > Include Library > Manage Libraries`, then search and install.

---

## Design Notes / Why Two Versions

A DC fan/motor wasn't available for the physical build, so the project uses whatever is available on each platform:

- **Simulation (Tinkercad)** — TMP36 (simplest analog sensor to simulate) + DC motor (standard fan substitute, switched via NPN transistor)
- **Real hardware** — DHT11 (physically available sensor) + 28BYJ-48 stepper motor with ULN2003 driver (physically available motor, since no DC motor/fan was on hand)

Both achieve the same functional goal — visual + mechanical response to temperature — using components suited to what's actually available on each platform.

---

## Troubleshooting Notes

- **TMP36 reading exactly 450°C** → A0 is reading a constant 5V, usually caused by VCC and OUT pins being swapped on the sensor.
- **DHT11 printing "Failed to read from DHT sensor!"** → check the 10kΩ pull-up resistor (if using a bare sensor) and confirm DATA is wired to pin 7.
- **Stepper motor silent** → the 28BYJ-48 is very quiet at low RPM; check the ULN2003 board's onboard LEDs for a blinking sequence to confirm signals are reaching it, and verify the external 5V supply is connected (Arduino's 5V pin can't power it reliably).
- **DC motor not spinning (simulation)** → check transistor pinout (Emitter–Base–Collector order), confirm the 1kΩ resistor sits between the Arduino pin and the base (not in the motor's power path), and confirm the motor's positive lead is tied to the power rail.

---

## Future Improvements

- Add an LCD/OLED display for live temperature readout
- Log temperature data over Serial to a computer for tracking over time
- Add a buzzer for high-temperature alerts
- Replace fixed thresholds with a potentiometer for adjustable trigger points
