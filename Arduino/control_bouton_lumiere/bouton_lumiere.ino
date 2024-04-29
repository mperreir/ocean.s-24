#include <Adafruit_NeoPixel.h>  


int temps_defini = 2000;    //définition du temps de maintien désiré en ms     
int boutonPin1 = 8;         // num pin du bouton
long debut_appui1;          // temps d'appui du bouton
bool variable1 = false;     // si le bouton est toujours appuye
bool longpress = false;     // si le bouton respecte le temps d'appui
int etat_bouton1;           // etat du bouton (0=relacher, 1=appuie)
int dernier_etat_bouton1 = 0; // etat du bouton a la boucle precedente

// Objet bande de led (utile pour la liaison avec le num pin)
struct LEDStrip {
  int pin;
  int numLEDs;
  Adafruit_NeoPixel strip;
};

const int numStrips = 5;    // nombre de bande led branche
LEDStrip myLEDStrips[numStrips] = {   // num pin des bandes led
  {6, 200},
  {5, 200},
  {4, 200},
  {3, 200},
  {2,200}
};

// fonction pour gerer l'initialisation d'une bande de led
void initNeoPixel(Adafruit_NeoPixel &strip, int pin, int numLEDs) {
  strip = Adafruit_NeoPixel(numLEDs, pin, NEO_GRB + NEO_KHZ800);
  strip.begin();
  strip.show();
}

// fonction pour initialise toutes les bandes de led
void initLEDStrips(LEDStrip *strips, int numStrips) {
  for (int i = 0; i < numStrips; i++) {
    initNeoPixel(strips[i].strip, strips[i].pin, strips[i].numLEDs);
  }
}

// fonction pour eteindre les leds
void clear() {
  for (int i = 0; i < numStrips; i++) {
    myLEDStrips[i].strip.clear();
    myLEDStrips[i].strip.show();
  }
}

// fonction pour changer la couleur des bandes led selons le niveau donnee en param
void level(int level) {
  clear();
  for (int i = 0; i < level; i++) {
    //myLEDStrips[i].strip.clear();
    for (int j = 0; j < myLEDStrips[i].numLEDs; j++) {
      myLEDStrips[i].strip.setPixelColor(j, myLEDStrips[i].strip.Color(0, 0, 139));
    }
    if (i == level - 1) {
      for (int j = 0; j < myLEDStrips[i].numLEDs; j++) {
        myLEDStrips[i].strip.setPixelColor(j, myLEDStrips[i].strip.Color(16,109,156));
    }
    }
    myLEDStrips[i].strip.show();
  }
  for (int i = level; i < numStrips; i++) {
    //myLEDStrips[i].strip.clear();
    for (int j = 0; j < myLEDStrips[i].numLEDs; j++) {
      myLEDStrips[i].strip.setPixelColor(j, myLEDStrips[i].strip.Color(35, 50, 5));
    }
    myLEDStrips[i].strip.show();
  }
}

// fonction pour appele la fonction level avec le bon niveau de config (donner en param)
void step(int s) {
  if (s > 0 && s <= 3) {
    level(s+2);
  } else{
    clear();
  }
}

void setup()   {       
  Serial.begin(9600);
  pinMode(boutonPin1, INPUT);
  initLEDStrips(myLEDStrips, numStrips);
}

void loop()   {

  //
  //  Gestion des lumières
  //

  if (Serial.available() > 0) {   // voir si il y a quelque chose dans le buffer (input dans le port serie)
    char s = Serial.read();       // recupere le premier caractere
    //Serial.print("Lecture : ");
    //Serial.println(s);
    if (s != 'N' && s!= 'S' && s != '\n') {   // si le format d'entre est correcte
      step(s - '0');
    }
  }

  //
  //  Gestion du bouton
  //

  etat_bouton1 = digitalRead(boutonPin1);    
  //Serial.println(etat_bouton1);                   //lecture de l'état des boutons
  if (etat_bouton1 == 1 && dernier_etat_bouton1 == 0){      //détection de l'appui sur le bouton 1
      debut_appui1 = millis();                                   //initialisation du compteur 1
      variable1 = true;                                          //enregistrement du changement d'état du bouton 1
  }
  if ( variable1 == true && etat_bouton1 == 1 && dernier_etat_bouton1 == 1){    //le bouton 1 était et est toujours appuyé                                                                         
      if ((millis() - debut_appui1) >= temps_defini){             //est-ce que le temps choisi est écoulé ?                                 
        longpress = true;                          
      }             
  }

  // quand on relache le bouton
  if (etat_bouton1 == 0 && dernier_etat_bouton1 != 0){                              
      
      variable1 = false;
      if(longpress) {
        longpress = false;
        // on commence l'animation
        Serial.println("S");
        //step(3); // alume les leds selon la configuration prevu pour l'étape 1
      }
      else {
        // on passe a l'étape suivante 
        Serial.println("N");
      }
  }
  dernier_etat_bouton1 = etat_bouton1;                       //actualisation de l'état du bouton
  delay(10);
}

