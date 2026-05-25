#include <I2CSoilMoistureSensor.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
const char* ssid = "uwase";
const char* password = "1234567890";
const char* servername = "http://192.168.137.1/DHT/insert.php";
#define sensorpin A0
#define relaypin D5
void setup() {
  Serial.begin(115200);
  pinMode(sensorpin, INPUT);
  pinMode(relaypin, OUTPUT);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nWiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}
void loop() {
int sensorvalue=analogRead(sensorpin);
Serial.print("sensorvalues:");
Serial.println(sensorvalue);
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;
    http.begin(client, servername);
    http.addHeader("Content-Type", "application/json");
    StaticJsonDocument<200> uwase;
    uwase["Moisture"] = "sensorvalue";
     uwase["device_name"] = "SoilMoisture";
    String jsonDoc;
    serializeJson(uwase, jsonDoc);
    int responseCode = http.POST(jsonDoc);
    Serial.print("Response Code: ");
    Serial.println(responseCode);
    if (responseCode > 0) {
      Serial.println("Data inserted successfully!");
    } else {
      Serial.println("Server failed");
    }
    http.end();
  } else {
    Serial.println("Failed to connect to WiFi");
  }
}

