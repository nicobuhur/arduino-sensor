## Arduino Temperature and Gas Monitoring System

### Introduction

The Arduino Temperature and Gas Monitoring System is a comprehensive project designed to observe room temperature and enhance safety through gas detection. The system utilizes a DHT11 temperature sensor, a Joyit SD card module for data storage, an MQ-2 gas sensor for safety, a buzzer for alerts, and LEDs for visual indication.

### Hardware Setup

The hardware configuration includes:

- DHT11 temperature sensor
- Joyit SD card module
- MQ-2 gas sensor
- 220-ohm resistors
- Buzzer
- LEDs

These components are interconnected as per the schematic diagram (see [Appendix A](#appendix-a)). The Arduino Uno board serves as the central processing unit, orchestrating the data collection and alert mechanisms.

### Software Implementation

The Arduino is programmed to execute specific functions based on temperature readings and gas sensor input. Code snippets for the temperature monitoring and gas detection logic are provided in [Appendix B](#appendix-b). The program ensures efficient utilization of the DHT11, Joyit SD card module, MQ-2 gas sensor, and other connected components.

### Temperature Monitoring

The system categorizes temperature into predefined ranges, each corresponding to a unique LED configuration:

- Below 20°C: Blue LED is active.
- 20-22°C: Blue and green LEDs are active.
- 22-24°C: Only green LED is active.
- 24-26°C: Green and red LEDs are active.
- Above 26°C: Only red LED is active, accompanied by a buzzer alert.

These temperature ranges align with the project's motivation, allowing users to adjust heating systems for optimal living conditions, contributing to energy-saving efforts.

### Gas Sensor and Buzzer

#### MQ-2 Gas Sensor

The MQ-2 gas sensor continuously monitors the environment by measuring the concentration of various gases. In this project, it specifically detects the presence of harmful gases. The gas sensor outputs an analog signal, and the Arduino reads this signal through analog pin A0.

#### Buzzer

The buzzer serves as an auditory indicator in the system. It is activated under specific conditions:

- **Temperature Threshold:** The temperature threshold for activating the buzzer is set to temperatures above 26°C. When the temperature surpasses this threshold, the red LED is illuminated, and the buzzer emits a short beep to draw attention to the elevated temperature.
- **Gas Detection:** The gas sensor checks for the presence of harmful gases, and if the gas sensor value exceeds the predefined threshold (200 in this project), the buzzer activates. Upon gas detection, the buzzer emits a series of short beeps for immediate alerting. This provides an early warning system for potential gas-related hazards.

### SD Card Module

The Joyit SD card module facilitates the storage of temperature and humidity data at regular intervals. It operates using the SPI communication protocol and is connected to the Arduino Uno through the chip select (CS) pin (pin 10 in this project). The system records temperature and humidity data to a file named "data.txt" at predefined intervals (in this project, values after an hour are recorded), ensuring a consistent and organized data collection process. This data can later be retrieved for analysis or record-keeping.

### Motivation and Impact

The motivation behind this project is rooted in the need for efficient energy consumption and enhanced safety. By monitoring room temperature using the DHT11 sensor, users can make informed decisions to optimize heating systems, contributing to energy-saving initiatives. This, in turn, has the potential to reduce heating bills, benefiting local economies. Furthermore, the integration of the MQ-2 gas sensor adds a crucial layer of safety, addressing concerns related to gas leaks or smoke.

### Conclusion

In conclusion, the Arduino Temperature and Gas Monitoring System offers a holistic solution for room temperature observation and safety, utilizing the DHT11, Joyit SD card module, and MQ-2 gas sensor. The project's unique features, such as LED-based temperature indication and gas detection alerts, make it a valuable tool for homeowners striving for energy efficiency and a secure living environment.

### Appendices

#### Appendix A: Schematic Diagram
![alt text](main/Picture 1.png)

#### Appendix B: Code Snippets
*Provide code snippets for temperature monitoring and gas detection logic here*
