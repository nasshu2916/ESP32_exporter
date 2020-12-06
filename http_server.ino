#include <ESPmDNS.h>
#include <WebServer.h>
#include <WiFi.h>
#include <WiFiClient.h>

#include "wifi_credentials.hpp"

WebServer server(80);

void setupNetwork(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
}

void handleRoot() { server.send(200, "text/plain", "hello from esp32!"); }

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void handleMetrics() { server.send(200, "text/plain", getMetrics()); }

void handleCO2() {
  int CO2 = myMHZ19.getCO2();
  int8_t Temp = myMHZ19.getTemperature();
  
  String message = "{";
  message += "\"CO2 (ppm)\": " + String(CO2) + ", ";
  message += "\"Temperature (C)\": " + String(Temp);
  message += "}";
  server.send(200, "application/json", message);
}

void handleBME680() {
  int32_t temp, humidity, pressure, gas;
  BME680.getSensorData(temp, humidity, pressure, gas);
  float alt = altitude(pressure);

  String message = "{";
  message += "\"Temperature\": " + String(temp / 100.0) + ", ";
  message += "\"Humidity\": " + String(humidity / 1000.0) + ", ";
  message += "\"AtmosphericPressure\": " + String(pressure / 100.0) + ", ";
  message += "\"Altitude\": " + String(alt) + ", ";
  message += "\"Gas\": " + String(gas / 100.0);
  message += "}";

  server.send(200, "application/json", message);
}

void startWebServer() {
  server.on("/", handleRoot);
  server.on("/bme680", handleBME680);
  server.on("/co2", handleCO2);
  server.on("/metrics", handleMetrics);

  server.on("/inline",
            []() { server.send(200, "text/plain", "this works as well"); });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void httpServerLoop() { server.handleClient(); }
