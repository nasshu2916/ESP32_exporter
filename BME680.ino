#include <Zanshin_BME680.h> // Include the BME680 Sensor library

const uint32_t SERIAL_SPEED{115200}; ///< Set the baud rate for Serial I/O

BME680_Class BME680;

float altitude(const int32_t press, const float seaLevel = 1013.25);
float altitude(const int32_t press, const float seaLevel) {
  static float Altitude;
  Altitude = 44330.0 * (1.0 - pow(((float)press / 100.0) / seaLevel, 0.1903));
  return (Altitude);
}

void setupbme680() {
  Serial.println("Initializing BME680 sensor");

  while (!BME680.begin(I2C_STANDARD_MODE)) {
    Serial.print("-- Not find BME680 Trying again in 5 seconds. --\n");
    delay(5000);
  }

  BME680.setOversampling(TemperatureSensor, Oversample16);
  BME680.setOversampling(HumiditySensor, Oversample16);
  BME680.setOversampling(PressureSensor, Oversample16);
  BME680.setIIRFilter(IIR4);
  BME680.setGas(320, 150);
}
