//debut de code pour la réaction de la bande led en fonction des messages reçus
//la connection wifi s"établie et les interactions sont detectées
//un led se propage sur la bande led à chaque message reçu 
//la led bloque lorsqu'un  autre message est reçu, logique à corriger


#include <FastLED.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#define LED_PIN         14
#define NUM_LEDS        34
#define BRIGHTNESS      100
#define DELAY_TIME      300 //délai en millisecondes entre l'avancement des LEDs
#define TIMER_DELAY     10000 //intervalle pour les requêtes HTTP
#define MESSAGE_THRESHOLD 3 // seuil pour un changement de couleur
#define TIME_WINDOW     20000 // Fenêtre de temps pour ajuster les couleurs
#define DECREASE_THRESHOLD 5000 // Seuil en ms pour le retour vers des couleurs moins sombres

const char* ssid     = "le nome du wifi";
const char* password = "le mot de passe du wifii";

CRGB leds[NUM_LEDS];

struct Propagation {
  int position;
  unsigned long lastUpdateTime;
  CRGB color; //Couleur spécifique attribuée à la propagation au moment de l'émission
};

Propagation propagations[NUM_LEDS];
int numPropagations = 0;
unsigned long lastMessageTime = millis(); //Temps du dernier message pour la logique de diminution
int messageCount = 0;
int colorIndex = 0;

CRGB colors[] = {CRGB::White, CRGB::Yellow, CRGB::Orange, CRGB::Red};
int numColors = sizeof(colors) / sizeof(colors[0]);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
}

void loop() {
  unsigned long currentTime = millis();

  // Reucupere donnée sur le serveura a chaque timer_delay
  if (currentTime - lastMessageTime > TIMER_DELAY) {
    fetchData();
  }

  //Diminue la couleur après une période prolongée sans nouveaux messages
  if (currentTime - lastMessageTime > TIME_WINDOW && colorIndex > 0) {
    if (currentTime - lastMessageTime > DECREASE_THRESHOLD) {
      colorIndex--;
      lastMessageTime = currentTime;
    }
  }

  for (int i = 0; i < numPropagations; i++) {
    if (currentTime - propagations[i].lastUpdateTime >= DELAY_TIME) {
      updatePropagation(i, currentTime);
    }
  }

  FastLED.show();
}

void fetchData() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure(); // pour HTTPS sans vérification de certificat
    HTTPClient http;
    http.begin(client, "https://hyblab.polytech.univ-nantes.fr/ocean-2/messages");

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(response);
      recevoirMessage(); //Appel de fonction pour signaler la réception d'un message
    } else {
      Serial.print("Error on HTTP request: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}

void recevoirMessage() {
  messageCount++;
  unsigned long currentTime = millis();

  if (messageCount >= MESSAGE_THRESHOLD && colorIndex < numColors - 1) {
    colorIndex++;
    messageCount = 0; //Réinitialiser le compteur après changement de couleur
  }

  lastMessageTime = currentTime; // Mise à jour du temps pour la dernière activité
  triggerLED(currentTime); // Déclenchement d'une nouvelle propagation de LED
}

void triggerLED(unsigned long currentTime) {
  if (numPropagations < NUM_LEDS) {
    propagations[numPropagations].position = 0;
    propagations[numPropagations].lastUpdateTime = currentTime;
    propagations[numPropagations].color = colors[colorIndex];
    numPropagations++;
  }
}

void updatePropagation(int index, unsigned long currentTime) {
  Propagation &prop = propagations[index];
  
  if (prop.position < NUM_LEDS) {
    leds[prop.position] = prop.color;
    prop.position++;
    prop.lastUpdateTime = currentTime;
  } else {
    // retirer la propagation à la fin de la bande
    removePropagation(index);
  }
}

void removePropagation(int index) {
  numPropagations--;
  for (int i = index; i < numPropagations; i++) {
    propagations[i] = propagations[i + 1];
  }
}
