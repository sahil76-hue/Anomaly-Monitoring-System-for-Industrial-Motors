ESP32-Based Industrial Motor Anomaly Detection System (IoT + ThingSpeak)

This project implements a real-time industrial motor anomaly detection system using an ESP32 microcontroller and multiple environmental + operational sensors. The system monitors temperature, humidity, motion interference, and motor current, detects abnormal conditions, triggers alerts locally, and uploads telemetry to the cloud for visualization and analysis.

Overview

The system continuously reads sensor data and evaluates predefined anomaly thresholds. If unsafe conditions occur, it activates a buzzer alert and suspends normal motor behavior. Otherwise, it operates normally and uploads sensor readings to ThingSpeak every 15 seconds for remote monitoring.

Designed for:

predictive maintenance experiments
industrial safety monitoring
academic IoT research projects
cloud-based anomaly analytics pipelines
Hardware Used
ESP32 Development Board
DHT22 Temperature & Humidity Sensor
ACS712 Current Sensor
PIR Motion Sensor
Servo Motor
Active Buzzer
External 5V supply (recommended for servo stability)
Sensor Parameters Monitored
Parameter	Sensor	Purpose
Temperature	DHT22	Detect overheating
Humidity	DHT22	Detect unsafe environment
Motion	PIR	Detect unauthorized interference
Motor Current	ACS712	Detect overload condition
Anomaly Conditions

Alert triggers when any condition is true:

Temperature > 60°C
Humidity > 80%
Motion detected near motor
Current > 2A

When triggered:

buzzer activates 🔔
servo stops scanning
anomaly logged to serial monitor
abnormal state visible in cloud data
Cloud Integration

Sensor data is transmitted to ThingSpeak using HTTP:

Field	Data
Field 1	Temperature
Field 2	Humidity
Field 3	Motion status
Field 4	Motor current

Update interval: 15 seconds

This enables:

remote monitoring 🌐
live graphs
anomaly trend tracking
dataset generation for research
System Workflow
Initialize ESP32 and sensors
Connect to WiFi
Calibrate ACS712 offset
Read sensor values
Detect anomaly conditions
Trigger buzzer if abnormal
Upload data to ThingSpeak
Repeat continuously
Key Features
real-time anomaly detection ⚡
ACS712 offset auto-calibration
multi-sensor fusion monitoring
cloud telemetry logging
servo activity control logic
buzzer-based alert mechanism
scalable architecture for MQTT / ML upgrades
Applications
industrial motor protection
predictive maintenance systems
smart factory monitoring
intrusion detection near machinery
academic IoT experimentation
cloud-based equipment diagnostics
Future Improvements
RMS current measurement for AC motors
MQTT-based streaming instead of HTTP
edge anomaly classification using TinyML
dashboard automation with alerts
mobile notification integration 📲
