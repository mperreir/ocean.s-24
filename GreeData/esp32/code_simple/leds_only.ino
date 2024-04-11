//Telecharger Arduino ide
//Installer la librairie FastLED

//Définir le nombre de LED et le pin de sortie
//Définir la luminosité et le délai
//Définir le seuil de message
//Définir les couleurs

//Vous aurez besoin d'une esp32 (esp32 dev modules dans le boards manager) et d'une bande de LED, 3 fils pour la connexion et le cable pour lesp

#include <FastLED.h>

#define LED_PIN    14
#define NUM_LEDS   180
#define BRIGHTNESS 100
#define DELAY_TIME 100  
#define MESSAGE_THRESHOLD 10 

CRGB leds[NUM_LEDS];
uint8_t ledPositions[NUM_LEDS];  //*les positions des LED
CRGB colors[] = {CRGB::White, CRGB::Orange, CRGB::Red};
uint8_t numColors = sizeof(colors) / sizeof(CRGB);
uint8_t colorIndex = 0;
uint8_t messageCount = 0;

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  clearLedPositions();
}

void loop() {
  static unsigned long lastMessageTime = 0;
  if (millis() - lastMessageTime > 1000) {
    lastMessageTime = millis();
    receiveMessage();
  }

  propagateLEDs();
  FastLED.show();
  delay(DELAY_TIME);
}

void receiveMessage() {
  messageCount++;
  if (messageCount >= MESSAGE_THRESHOLD) {
    colorIndex = (colorIndex + 1) % numColors;
    messageCount = 0;
  }
  triggerNewLED();
}

void triggerNewLED() {
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    if (ledPositions[i] == 0) {
      ledPositions[i] = 1;
      break;
    }
  }
}

void propagateLEDs() {
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    if (ledPositions[i] > 0) {
      leds[ledPositions[i] - 1] = CRGB::Black;  //Éteindre l'ancienne position
      ledPositions[i]++;
      if (ledPositions[i] <= NUM_LEDS) {
        leds[ledPositions[i] - 1] = colors[colorIndex];  //Allumer la nouvelle position avec la couleur actuelle
      } else {
        ledPositions[i] = 0;  //Réinitialiser la position si la LED a atteint la fin
      }
    }
  }
}

void clearLedPositions() {
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    ledPositions[i] = 0;
  }
}