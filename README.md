# solar-power-bank-stm32
Solar power bank using STM32 with PWM-based charging, battery monitoring, and buck converter output
# Solar Power Bank with STM32 (Charge Control + Monitoring)

 Overview

This project implements a **solar-powered battery charging and monitoring system** using an STM32 microcontroller.

The system uses an **18V solar panel, a MOSFET-based switching circuit**, and **dual voltage sensing** to control charging and monitor system behavior in real time.

Features

 Solar energy harvesting using 18V panel
 MOSFET-based charge control using PWM
 Dual voltage monitoring (solar + battery)
 STM32 ADC-based sensing
 Voltage divider protection for ADC inputs
 Battery status estimation
 USB output using buck converter



 Components Used

* STM32F103C8 (Blue Pill)
* 18V Solar Panel
* N-Channel MOSFET (IRLZ44N / AO4407 equivalent)
* Li-ion Battery (3.7V, 4.2V max)
* Buck Converter (5V output)
* Schottky Diode (SS34)
* Resistors (for voltage divider and gate control)

System Architecture :

![Architecture Diagram]architecture.png

 Circuit Description

 1. Solar Voltage Sensing

 Voltage divider reduces 18V → < 3.3V
 Connected to STM32 ADC (PA1)

2. Battery Voltage Sensing

* Voltage divider reduces battery voltage → safe ADC level
* Connected to STM32 ADC (PA0)

3. MOSFET Gate Drive

STM32 PWM (PA2) → 100Ω resistor → MOSFET Gate
Gate → 10kΩ pull-down → GND

Ensures stable switching
Prevents floating gate
Protects STM32 GPIO

4. Charging Path

Solar → Diode → MOSFET → Battery

Diode prevents reverse current
MOSFET controls charging



5. Output Stage

Battery → Buck Converter → 5V USB Output


 Working Principle

1. STM32 reads solar voltage and battery voltage using ADC
2. Voltages are scaled using voltage divider equations
3. System checks charging condition:



4. STM32 generates PWM signal to control MOSFET
5. Battery supplies regulated output through buck converter

 Key Concepts

 Voltage Divider


Vout = Vin × (R2 / (R1 + R2))


 ADC Conversion

Voltage = (ADC_value × 3.3) / 4095


 PWM Control

* STM32 generates PWM signal
* Controls MOSFET switching
* Regulates charging behavior




 Battery Logic

* > 4.0V → FULL
* 3.5V – 4.0V → MEDIUM
* < 3.5V → LOW




Conclusion

This project demonstrates a **practical solar energy system integrated with STM32**, combining:

* Power electronics (MOSFET switching)
* Embedded systems (ADC + PWM)
* Energy management logic

It reflects real-world design considerations for **embedded and renewable energy systems**.

