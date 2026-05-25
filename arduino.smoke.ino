#include <WiFi.h>
#include <HTTPClient.h>

// WiFi credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// Your server URL
String serverName = "http://YOUR_SERVER_IP/smoke/insert.php";

// MQ-2 Sensor pin
int smokeSensor = 34;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {

  int smokeValue = analogRead(smokeSensor);

  Serial.print("Smoke Level: ");
  Serial.println(smokeValue);

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    String serverPath = serverName + "?smoke=" + String(smokeValue);

    http.begin(serverPath.c_str());

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }

  delay(5000);
}

}
