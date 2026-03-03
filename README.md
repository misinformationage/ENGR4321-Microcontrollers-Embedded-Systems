# Table of Contents
This repository contains a source-folder and project description for multiple ENGR 4321 Microcontroller and Embedded Systems projects. For organization and ease of access, the following links will route to each project description in this README.

- ([Exercise 5.5 Detect Human Movement](https://github.com/misinformationage/ENGR4321-Microcontrollers-Embedded-Systems?tab=readme-ov-file#exercise-55-detect-human-movement))
- ([Exercise 8.6 Temperature and Humidity Monitoring with Adafruit IO](https://github.com/misinformationage/ENGR4321-Microcontrollers-Embedded-Systems?tab=readme-ov-file#exercise-86-temperature-and-humidity-monitoring-with-adafruit-io))
- ([Project 1: Smart Greenhouse](https://github.com/misinformationage/ENGR4321-Microcontrollers-Embedded-Systems?tab=readme-ov-file#project-1-smart-greenhouse))

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
The ESP32 reads the digital signal from the PIR motion sensor, interpretting the presence of motion as either a 0 "false" or 1 "true". In Wokwi this is done by clicking on the sensor during the simulation, and then toggling a popup. During the setup phase of the code, the LCD, LED, and serial port of the ESP32 are intialized. For the remainder of the code, an IF statement loops. This IF statement checks whether the PIR sensor is reporting motion or not, then displays the relevant message to the LCD. If motion is detected, the LED will be activated. After a delay, this logic is looped until motion is no longer being reported by the PIR sensor.

## Block Diagram
<img width="351" height="232" alt="Ex5 5_Block_Diagram" src="https://github.com/user-attachments/assets/4bdcc530-9ef9-4a8b-93f8-c69add50cabd" />

# [Exercise 8.6 Temperature and Humidity Monitoring with Adafruit IO]

**Course:** ENGR 4321 Microcontroller and Embedded Systems  
**Student:** Skylar Stanke  
**Date:** February 23rd 2026  

## Project Overview
This project uses the ESP32's WiFi capability to connect to an Adafruit IO dashboard, using it to store temperature and humidity values from a local DHT22 sensor. Additionally, the dashboard is used to remotely control the power of an LED.

## Hardware Components (Simulated)
* **Microcontroller:** ESP32 DevKit V1  
* **Input:** [DHT22 Sensor, Adafruit IO Dashboard]  
* **Output:** [Adafruit IO Dashboard, LED]  

## Simulation Link
[Click here to view the Wokwi Simulation](https://wokwi.com/projects/456415876763237377)

## How It Works

The ESP32 uses WiFi, MQTT, and the Adafruit API to subscribe and publish to data feeds. These data feeds are accessable through a dashboard setup on an Adafruit IO account, where "temperature" and "humidity" are displayed, as well as a toggle switch for the "LED" feed. The ESP32 subscribes to the "LED" feed to receive information, and publishes to the "temperature" and "humidity" feeds using analog data it read from a DHT22 sensor. When the "LED" feed returns a value of "ON" to the ESP32, it sets the LED state to HIGH, otherwise it reverts back to LOW state. To maintain connectivity, the MQTT server attempts a reconnection every void loop, as well as refuses to publish values to feeds that are NaN.

## Block Diagram
<img width="486" height="292" alt="Ex8 6_Block_Diagram" src="https://github.com/user-attachments/assets/c9dc3d96-d276-4f60-8457-144f04a74063" />

# [Project 1: Smart Greenhouse]

**Course:** ENGR 4321 Microcontroller and Embedded Systems  
**Student:** Skylar Stanke  
**Date:** March 2n. 2026  

## Project Overview
This project expands upon previous exercises, using sensors, data pulled from OpenWeather API, and Wifi capability to publish to an Adafruit IO dashboard. The dashboard, as well as an LED, LCD, and buzzer function to alert plant owners when negative conditions have been reported in a greenhouse that the ESP32 resides in.

## Hardware Components (Simulated)
* **Microcontroller:** ESP32 DevKit V1  
* **Input:** [DHT22 Sensor, Light Sensor, PIR Motion Sensor, OpenWeather API]  
* **Output:** [Adafruit IO Dashboard, RGB LED, Buzzer, I2C LCD]  

## Simulation Link
[Click here to view the Wokwi Simulation](https://wokwi.com/projects/456779664065616897)

## How It Works

On startup the ESP32 establishes connections to Adafruit IO and OpenWeather, and then maintains these connections throughout the loop. It then collects and processes data from the light sensor, DHT22 sensor, and PIR motion sensor, and runs it through logic checks to determine two messages. One message is for if motion is detected by the PIR sensor, and the other message is for temperature being too hot or cold. Next the ESP32 displays the two messages on the LCD, activates the buzzer and changes the LED color accordingly, and publishes the data to the dashboard. After delaying the loop to prevent API limits, it repeats again.

## Block Diagram
<img width="681" height="581" alt="Project1_Block_Diagram" src="https://github.com/user-attachments/assets/b2de53b1-eb5d-40e8-8c3d-d0c25570597f"/>
