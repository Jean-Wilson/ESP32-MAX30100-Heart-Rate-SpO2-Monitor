#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

PulseOximeter pox;

uint32_t lastBeat = 0;

void onBeatDetected() {
  Serial.println("Beat!");
}

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing pulse oximeter...");

  if (!pox.begin()) {
    Serial.println("FAILED to initialize MAX30100!");
    for(;;);
  } else {
    Serial.println("SUCCESS");
  }

  // Register callback for beat detection
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
  // Call update frequently
  pox.update();

  // Display heart rate & SpO2 once per second
  if (millis() - lastBeat > 1000) {
    Serial.print("Heart rate: ");
    Serial.print(pox.getHeartRate());
    Serial.print(" bpm / SpO2: ");
    Serial.print(pox.getSpO2());
    Serial.println(" %");

    lastBeat = millis();
  }
}
