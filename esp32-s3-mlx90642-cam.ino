// Board bring-up: print what the firmware sees before adding sensor code.
// Arduino IDE Tools settings are listed in README.md.

void setup() {
  Serial.begin(115200);
  delay(1000);

  uint16_t rev = ESP.getChipRevision();  // format: major * 100 + minor

  Serial.printf("Arduino-ESP32 %s (ESP-IDF %s)\n", ESP_ARDUINO_VERSION_STR, esp_get_idf_version());
  Serial.printf("chip %s, revision v%u.%u, %u core(s), %lu MHz\n",
                ESP.getChipModel(), rev / 100, rev % 100, ESP.getChipCores(),
                (unsigned long)ESP.getCpuFreqMHz());
  Serial.printf("flash %lu MB\n", (unsigned long)(ESP.getFlashChipSize() / (1024 * 1024)));

  if (psramFound()) {
    Serial.printf("psram %lu MB\n", (unsigned long)(ESP.getPsramSize() / (1024 * 1024)));
  } else {
    Serial.println("psram not found (check Tools > PSRAM: OPI PSRAM)");
  }
}

void loop() {
}
