#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#include <ESP32Servo.h>

#define DHTPIN 4
#define DHTTYPE DHT11

#define PIR_PIN 21
#define SERVO_PIN 19
#define BUZZER 23
#define CURRENT_PIN 32  

const char* ssid = "Throttling the Network";
const char* password = "Sahil@mac";

String apiKey = "8L8C8TD2ZVM8X3GO";

DHT dht(DHTPIN, DHTTYPE);
Servo motorServo;

int angle = 0;


float offsetVoltage = 0;   
float maxVoltage = 3.3;    

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);

  motorServo.attach(SERVO_PIN);
  dht.begin();

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");


  Serial.println("Calibrating ZERO (no current)...");
  float sum = 0;
  for (int i = 0; i < 500; i++) {
    sum += analogRead(CURRENT_PIN);
    delay(2);
  }
  float avgOffset = sum / 500.0;
  offsetVoltage = (avgOffset / 4095.0) * 3.3;

  Serial.print("Offset Voltage: ");
  Serial.println(offsetVoltage);


  Serial.println("Set potentiometer to MAX (20A)...");
  delay(5000);

  float sumMax = 0;
  for (int i = 0; i < 500; i++) {
    sumMax += analogRead(CURRENT_PIN);
    delay(2);
  }
  float avgMax = sumMax / 500.0;
  maxVoltage = (avgMax / 4095.0) * 3.3;

  Serial.print("Max Voltage: ");
  Serial.println(maxVoltage);
}

void loop() {


  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  int pirState = digitalRead(PIR_PIN);


  float sum = 0;
  for (int i = 0; i < 50; i++) {
    sum += analogRead(CURRENT_PIN);
    delay(2);
  }
  float avg = sum / 50.0;

  float voltage = (avg / 4095.0) * 3.3;


  float current = ((voltage - offsetVoltage) / (maxVoltage - offsetVoltage)) * 20.0;


  if (current < 0) current = 0;
  if (current > 20) current = 20;


  if (current < 0.2) {
    offsetVoltage = (0.99 * offsetVoltage) + (0.01 * voltage);
  }


  Serial.println("------Sensor Readings------");
  Serial.print("Temp: "); Serial.println(temp);
  Serial.print("Humidity: "); Serial.println(humidity);
  Serial.print("PIR: "); Serial.println(pirState);
  Serial.print("Current: "); Serial.println(current);


  bool anomaly = false;

  if (temp > 60) anomaly = true;
  if (humidity > 80) anomaly = true;
  if (pirState == HIGH) anomaly = true;
  if (current > 2.0) anomaly = true;


  if (anomaly) {
    Serial.println("ANOMALY DETECTED");
    digitalWrite(BUZZER, HIGH);
  } else {
    digitalWrite(BUZZER, LOW);

    motorServo.write(angle);
    angle += 10;
    if (angle > 180) angle = 0;

    delay(200);
  }


  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = "http://api.thingspeak.com/update?api_key=" + apiKey +
                 "&field1=" + String(temp) +
                 "&field2=" + String(humidity) +
                 "&field3=" + String(pirState) +
                 "&field4=" + String(current);

    http.begin(url);
    int httpCode = http.GET();

    Serial.print("ThingSpeak Response: ");
    Serial.println(httpCode);

    http.end();
  }

  delay(15000); 
}