# ESP32 Prometheus Exporter
It is an exporter for Prometheus of MH-Z19 and BME680 using ESP32.

## Setting
Create WiFi credentials at `wifi-credentials.hpp` as follows:
``` c
const char *ssid = "<wifi ssid>";
const char *password = "<wifi password>";
```

The service runs on port 80.

## Necessary Library

https://github.com/WifWaf/MH-Z19  
https://github.com/SV-Zanshin/BME680
