#include "MHZ19.h"

#define RX_PIN 16
#define TX_PIN 17 

MHZ19 myMHZ19;
HardwareSerial hwSerial(2);

void setupMHZ19() {
  hwSerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  myMHZ19.begin(hwSerial);
  myMHZ19.autoCalibration(false);
}