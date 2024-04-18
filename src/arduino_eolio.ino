#include <ErriezRobotDyn4DigitDisplay.h>

// Définition des broches des boutons
int bp1 = 12;
int bp2 = 13;

// Définition des broches du joystick
const int pinUp = 4;
const int pinDown = 3;
const int pinLeft = 2;
const int pinRight = 5;

// Définition des broches de l'écran affichant l'année.
#define CLK 7  
#define DIO 8  

// Create display object
RobotDyn4DigitDisplay display(CLK, DIO);

// Variable pour stocker la valeur reçue depuis le port série
int timeIndex = 1;
int data = 1;

// Variables pour garder une trace de l'état précédent des boutons
int prevBp1State = HIGH;
int prevBp2State = HIGH;

// Variable pour contrôler la temporisation
unsigned long lastButtonPressTime = 0;
const unsigned long debounceDelay = 50; // Définir le délai de rebondissement en millisecondes

void setup()
{
  // Initialize TM1637
  display.begin();
  display.setBrightness(7); // Maximum

  // Bouton poussoir 1
  pinMode(bp1, INPUT_PULLUP);
  // Bouton poussoir 2
  pinMode(bp2, INPUT_PULLUP);

  // Initialisation des broches en entrée du joystick avec la résistance de pull-up activée
  pinMode(pinUp, INPUT_PULLUP);
  pinMode(pinDown, INPUT_PULLUP);
  pinMode(pinLeft, INPUT_PULLUP);
  pinMode(pinRight, INPUT_PULLUP);

  Serial.begin(115200);
}

void loop()
{
  // Lire les données envoyées depuis le port série
  if (Serial.available() > 0) {
    data = Serial.parseInt();
  }

  if (data != 9 && data != 0) {
    timeIndex = data; // Lire l'entier envoyé depuis le port série
  }

  // Récupérer la valeur de bp1
  int b1 = digitalRead(bp1);
  // Récupérer la valeur de bp2
  int b2 = digitalRead(bp2);

  // Lecture des états des boutons du joystick
  int stateUp = digitalRead(pinUp);
  int stateDown = digitalRead(pinDown);

  // Si l'état précédent de bp1 était HIGH et l'état actuel est LOW (appui)
if (prevBp1State == HIGH && b1 == LOW && millis() - lastButtonPressTime > debounceDelay) {
  Serial.println("1");
  lastButtonPressTime = millis(); // Mettre à jour le temps du dernier appui
}

// Si l'état précédent de bp2 était HIGH et l'état actuel est LOW (appui)
else if(prevBp2State == HIGH && b2 == LOW && millis() - lastButtonPressTime > debounceDelay) {
  Serial.println("2");
  lastButtonPressTime = millis(); // Mettre à jour le temps du dernier appui
}

// Si l'état précédent de bp1 était LOW et l'état actuel est HIGH (relâchement)
if (prevBp1State == LOW && b1 == HIGH && millis() - lastButtonPressTime > debounceDelay) {
  Serial.println("9");
}

// Si l'état précédent de bp2 était LOW et l'état actuel est HIGH (relâchement)
if (prevBp2State == LOW && b2 == HIGH && millis() - lastButtonPressTime > debounceDelay) {
  Serial.println("9");
}

// Mise à jour de l'état précédent des boutons
prevBp1State = b1;
prevBp2State = b2;


  // Si Appuie JoyStick Up
  if(stateUp == LOW) {
    Serial.println("3");
    Serial.println("9");
  }

  // Si Appuie JoyStick Down
  else if(stateDown == LOW) {
    Serial.println("4");
    Serial.println("9");
  }

  // Utiliser la valeur reçue pour afficher sur l'écran
  switch (timeIndex) {
    case 1:
      display.dec(2022);	// 9 9 9 9
      break;
    case 2:
      display.dec(2022);	// 9 9 9 9
      break;
    case 3:
      display.dec(2024);
      break;
    case 4:
      display.dec(2028);
      break;
    case 5:
      display.dec(2035);
      break;
    case 6:
      display.dec(2035);
      break;
    default:
      display.dec(0000);
      break;
  }
}