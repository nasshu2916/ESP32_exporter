extern "C" {
uint8_t temprature_sens_read();
}

String getMetrics() {
  String p = "";

  int sketch_size = ESP.getSketchSize();
  int flash_size =  ESP.getFreeSketchSpace();
  int available_size = flash_size - sketch_size;
  float esp32_temperature = ((temprature_sens_read() - 32) / 1.8);
  
  int CO2 = myMHZ19.getCO2();
  float MHZ19_Temp = myMHZ19.getTemperature();

  int32_t BME680_temperature, humidity, pressure, gas;
  BME680.getSensorData(BME680_temperature, humidity, pressure, gas);
  float alt = altitude(pressure);

  setMetric(&p, "esp32_uptime", String(millis()));
  setMetric(&p, "esp32_wifi_rssi", String(WiFi.RSSI()));
  setMetric(&p, "esp32_heap_size", String(ESP.getHeapSize()));
  setMetric(&p, "esp32_free_heap", String(ESP.getFreeHeap()));
  setMetric(&p, "esp32_cpu_frequency", String(getCpuFrequencyMhz()));
  setMetric(&p, "esp32_sketch_size", String(sketch_size));
  setMetric(&p, "esp32_flash_size", String(flash_size));
  setMetric(&p, "esp32_available_size", String(available_size));
  setMetric(&p, "esp32_temperature", String(esp32_temperature));
  setMetric(&p, "MHZ19_CO2", String(CO2));
  setMetric(&p, "MHZ19_temperature", String(MHZ19_Temp));
  setMetric(&p, "BME680_temperature", String(BME680_temperature / 100.0));
  setMetric(&p, "BME680_humidity", String(humidity / 1000.0));
  setMetric(&p, "BME680_atmospheric_pressure", String(pressure / 100.0));
  setMetric(&p, "BME680_altitude", String(alt));
  setMetric(&p, "BME680_gas", String(gas / 100.0));

  return p;
}

void setMetric(String *p, String metric, String value) {
  *p += "# " + metric + "\n";
  *p += "# TYPE " + metric + " gauge\n";
  *p += "" + metric + " ";
  *p += value;
  *p += "\n";
}


