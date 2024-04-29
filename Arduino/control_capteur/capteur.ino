#include "Arduino.h"
#include "Wire.h"
#include <DFRobot_VL53L0X.h>

#define TCAADDR 0x70 // Adresse I2C du multiplexeur
#define NUM_SENSORS 5


// Déclaration de chaque capteur VL53L0X
DFRobot_VL53L0X sensors[NUM_SENSORS];

void tcaselect(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

void setup() {
  Serial.begin(57600);
  Wire.begin();
  // Initialisez chaque capteur dans une boucle
  for (uint8_t i = 0; i < NUM_SENSORS; i++) { 
    tcaselect(i); // Sélectionner le port du multiplexeur pour le capteur actuel
    delay(500); // Attendez un court instant pour que le multiplexeur s'initialise
    sensors[i].begin(); // Initialisez le capteur sans spécifier l'adresse
    sensors[i].setMode(sensors[i].eContinuous,sensors[i].eHigh);
    sensors[i].start();
  }
}

void loop() {
  // Lisez la distance de chaque capteur et affichez-la
  for (uint8_t i = 0; i < NUM_SENSORS; i++) { 
    tcaselect(i); // Sélectionner le port du multiplexeur pour le capteur actuel
    delay(10); // Attendez un court instant pour que le multiplexeur commute
    uint8_t dist = (uint8_t) sensors[i].getDistance();
    Serial.print(i);
    Serial.print(":");
    Serial.print(dist);
    Serial.print(";");
  }
  Serial.println();
  delay(500);
}