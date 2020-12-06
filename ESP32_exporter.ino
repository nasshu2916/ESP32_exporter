// #include <Preferences.h>

void setup(void) {
  Serial.begin(115200);

  setupNetwork();
  setupMHZ19();
  setupbme680();
  startWebServer();
}

void loop() { httpServerLoop(); }
