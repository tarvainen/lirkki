#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "***";
const char* password = "***";

void handlePostRoot();
void handle404();

ESP8266WebServer server(80);

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
  server.onNotFound(handle404);

  server.begin();
}

void loop() {
  server.handleClient();
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

void handle404() {
  server.send(404, "text/html", "Not found");
}
