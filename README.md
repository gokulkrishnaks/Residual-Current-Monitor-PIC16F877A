# Residual Current Monitor (PIC16F877A)

This project implements a simple residual current monitoring system using the PIC16F877A microcontroller.
It monitors the analog input voltage (0–5 V) representing current sensed from a measurement circuit and activates an LED indicator when the value exceeds a threshold.

This version uses a potentiometer in simulation to adjust the sensed level for easy testing and calibration.

---

## Features

* Single-channel current level measurement using ADC (AN0)
* Adjustable trigger threshold in firmware
* Visual alert through an LED on RB0
* Runs in Proteus simulation environment
* Clean and beginner-friendly embedded C code (XC8 + MPLAB X)

---

## How It Works

1. The input voltage (0–5 V) is applied to the AN0 pin of PIC16F877A.
   In real use, this would come from a current transformer and conditioning circuit.
2. The ADC continuously samples this voltage.
3. If the reading exceeds a predefined 10-bit threshold value:

   * The LED on RB0 is turned on.
4. Below the threshold:

   * The LED remains off.

Threshold value can be tuned inside the firmware code.

---

## Hardware / Simulation Setup

### Proteus Schematic (Potentiometer Version)

* Potentiometer:

  * Left → +5 V
  * Right → GND
  * Middle (wiper) → RA0/AN0 (Pin 2)
* LED output:

  * RB0 (Pin 33) → 330 Ω resistor → LED → GND
* Power:

  * Pin 11 (VDD) and Pin 32 → +5 V
  * Pin 12 (VSS) and Pin 31 → GND
* Clock:

  * No crystal required in schematic
  * Set clock frequency to **4 MHz** in PIC properties

---

## Firmware

Located in:
`firmware/main.c`

Written in **XC8** for **PIC16F877A**.

Key snippet:

```c
unsigned int v = adc_read_ch0();
if(v > THRESHOLD_ADC)
    RB0 = 1;
else
    RB0 = 0;
```

Adjust this constant to change sensitivity:

```c
#define THRESHOLD_ADC 512   // Half-scale of ADC (≈2.5V)
```

---

## Project Structure

```
Residual-Current-Monitor-PIC/
├─ firmware/
│  └─ main.c
├─ proteus/
│  └─ schematic.pdsprj  (to be added)
└─ README.md
```

---

## Future Enhancements

Planned improvements include:

* Dual-channel measurement (Live vs Neutral)
* Leakage detection by comparing two ADC channels
* Relay trip output for protection
* UART or LCD display of readings
* Proper calibration using real CT sensors
* PCB design for hardware deployment
* Safety isolation for mains operation

---

## Disclaimer

This project is intended for learning and simulation purposes only.
It is **not** a certified Residual Current Device and must not be used for real mains protection without proper electrical safety design and compliance to standards.

---
