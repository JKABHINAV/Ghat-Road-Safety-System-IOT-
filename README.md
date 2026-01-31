# Ghat-Road-Safety-System-IOT-
IoT-based collision avoidance system for blind curves using ESP32, IR sensors, and a real-time Web Dashboard.
# Ghat Road Safety System (IoT & Embedded Systems)

## 📌 Overview
This project is an automated safety system designed for blind curves on Ghat roads. It uses IR sensors to detect vehicles and provides cross-side alerts via buzzers to prevent collisions. It also features an ESP32-hosted web dashboard for real-time monitoring.

## 🛠️ Tech Stack
* **Microcontroller:** ESP32 (Dual Core)
* **Framework:** ESP-IDF / FreeRTOS
* **Language:** Low-level C
* **Protocols:** HTTP (Web Server), IEEE 802.11 (SoftAP), GPIO
* **Hardware:** IR Sensors, Active Buzzers

## 🚀 Key Features
* **Cross-Trigger Logic:** If Side A detects a vehicle, Side B's buzzer sounds.
* **Edge Detection:** Precise vehicle counting logic to prevent double-counting.
* **Web Dashboard:** Access traffic status and vehicle counts at `192.168.4.1`.
* **Reliability:** Built using FreeRTOS tasks for stable performance.

## 📸 Project Media
![System Image](your_image_filename.png)
*(Link your video here or upload it to the 'media' folder)*

## 🔧 Hardware Connections
- **IR Sensor A:** GPIO 4 | **IR Sensor B:** GPIO 5
- **Buzzer A:** GPIO 19 | **Buzzer B:** GPIO 22
