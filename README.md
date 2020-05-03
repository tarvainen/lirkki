# LIRKKI

Automatic plant watering system for my salads and tomatoes.

## IDE

Please use `Visual Studio Code` with `PlatformIO` plugin for development.

## Configuration

Before uploading to chip, configure WiFi settings to the beginning of the code (don't commit).

```
const char* ssid = "Your WiFi SSID";
const char* password = "Your WiFi password";
```

## Usage

Turn off watering

```
curl http://IP_OF_THE_ESP8266 --data "status=off"
```

Turn on watering

```
curl http://IP_OF_THE_ESP8266 --data "status=on"
```
