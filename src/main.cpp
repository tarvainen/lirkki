#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char* ssid = "***";
const char* password = "***";

void handlePostRoot();
void handleGetTime();
void handle404();
void updateTime();

ESP8266WebServer server(80);

WiFiUDP ntpUDP;

unsigned long timeLastUpdated = 0;

NTPClient timeClient(ntpUDP, "europe.pool.ntp.org");

void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  digitalWrite(LED_BUILTIN, HIGH);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
  }

  server.on("/", HTTP_POST, handlePostRoot);
  server.on("/time", HTTP_GET, handleGetTime);
  server.onNotFound(handle404);

  server.begin();

  timeClient.update();
}

void loop() {
  server.handleClient();

  updateTime();
}

void handlePostRoot() {
  String status = server.arg("status");

  if (status == "on") {
    digitalWrite(2, LOW);
  } else if (status == "off") {
    digitalWrite(2, HIGH);
  }

  server.send(200, "text/html", status);
}

void handleGetTime() {
  server.send(200, "text/html", String(timeClient.getEpochTime()));
}

void handle404() {
  server.send(404, "text/html", "Not found");
}

void updateTime() {
  if (millis() - timeLastUpdated > 60000) {
    timeClient.update();

    timeLastUpdated = millis();
  }
}
