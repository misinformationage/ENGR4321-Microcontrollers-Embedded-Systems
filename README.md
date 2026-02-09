# [Exercise 5.5 Detect Human Movement]

**Course:** ENGR 4321 Microcontroller and Embedded Systems  
**Student:** Skylar Stanke  
**Date:** February 9th 2026  

## Project Overview
This project uses a PIR motion sensor to detect movement, and then uses that input to display a message to an I2C LCD while flashing an LED. The message displayed to the LCD and the behavior of the LED are easily modifiable.

## Hardware Components (Simulated)
* **Microcontroller:** ESP32 DevKit V1  
* **Input:** [PIR Motion Sensor Module]  
* **Output:** [I2C LCD1602 Display, LED]  

## Simulation Link
[Click here to view the Wokwi Simulation](https://wokwi.com/projects/455456579481842689)

## How It Works
The ESP32 reads the digital signal from the PIR motion sensor, interpretting the presence of motion as either a 0 "false" or 1 "true". In Wokwi this is done by clicking on the sensor during the simulation, and then toggling a popup. During the setup phase of the code, the LCD, LED, and serial port of the ESP32 are intialized. For the remaineder of the code, an IF statement loops. This IF statement checks whether the PIR sensor is reporting motion or not, then displays the relevant message to the LCD. If motion is detected, the LED will be activated. After a delay, this logic is looped until motion is no longer being reported by the PIR sensor.
