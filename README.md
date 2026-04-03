# ESP32-Based Industrial Motor Anomaly Detection System

This project uses an ESP32 with DHT22, PIR, and ACS712 sensors to detect abnormal motor conditions such as overheating, high humidity, motion interference, and overcurrent. When an anomaly is detected, a buzzer alert is triggered and sensor data is sent to ThingSpeak for remote monitoring.

## Features
- Real-time temperature and humidity monitoring
- Motion detection using PIR sensor
- Current monitoring using ACS712
- Buzzer alert for abnormal conditions
- Cloud data logging on ThingSpeak
- Wi-Fi based remote monitoring

## Components Used
- ESP32 Development Board
- DHT22 Sensor
- PIR Sensor
- ACS712 Current Sensor
- Servo Motor
- Buzzer

## Pin Configuration
- DHT22 Data Pin → GPIO 4
- PIR Output → GPIO 21
- Servo Signal → GPIO 19
- Buzzer → GPIO 23
- ACS712 Output → GPIO 32

## Working
The ESP32 continuously reads temperature, humidity, PIR status, and motor current. If any value crosses the set threshold, the system marks it as an anomaly and activates the buzzer. The sensor readings are uploaded to ThingSpeak every 15 seconds for monitoring and analysis.

## Anomaly Conditions
- Temperature > 60°C
- Humidity > 80%
- Motion detected
- Current > 2A

## Libraries Used
- WiFi.h
- HTTPClient.h
- DHT.h
- ESP32Servo.h

