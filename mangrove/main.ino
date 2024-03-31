#include <Servo.h>

#define VIN 5 // V power voltage
#define R 10000 //ohm resistance value

// pins
constexpr uint8_t JOYSTICK_X = A5;
constexpr uint8_t JOYSTICK_Y = A4;
constexpr uint8_t LASER = 12;
constexpr uint8_t SERVO1 = 5;
constexpr uint8_t SERVO2 = 6;

Servo servo1;
Servo servo2;

// conversion "valeur pin photorésistance -> lumens"
int sensorRawToPhys(int raw){
  // Conversion rule
  float Vout = float(raw) * (VIN / float(1023));// Conversion analog to voltage
  float RLDR = (R * (VIN - Vout))/Vout; // Conversion voltage to resistance
  int phys=500/(RLDR/1000); // Conversion resitance to lumen

  return phys;
}

void setup() {
  Serial.begin(9600);

  pinMode(LASER, OUTPUT);

  servo1.attach(SERVO1);
  servo2.attach(SERVO2);

  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
}

// contraint une valeur à un intervalle [min; max]
template <typename T> T clamp(T value, T min, T max) {
  if (value < min) {
    return min;
  } else if (value > max) {
    return max;
  } else {
    return value;
  }
}

unsigned long lastJoystickRead = 0;

// délai nécessaire pour éviter que le joystick soit trop sensible
constexpr unsigned long JOYSTICK_INPUT_DELAY = 75;

// état global de l'activité
enum GlobalState {
  Inactive = 0, // inactif - l'utilisateur n'a pas touché au joystick depuis un moment
  Start = 1, // démarrage - l'utilisateur vient de toucher au joystick
  Active = 2, // actif
};

// état d'une zone en particulier
enum ZoneState {
  Blank = 0, // la zone n'est pas explorée
  Scanned = 1, // la zone a été scannée
  Probed = 2 // une balise a été installée dans la zone
};

// défini une zone scannable
struct Zone {
  uint8_t photo_cell_pin; // pin sur lequel la photorésistance de la zone est connecté

  ZoneState state; // état de la zone

  unsigned long lastStateChange; // dernière fois que l'état a changé

  bool isCandidate; // une balise peut être posée
};

#define NB_ZONES 4

Zone zones[NB_ZONES] = {
  {A0, Blank, 0, true},
  {A1, Blank, 0, false},
  {A2, Blank, 0, true},
  {A3, Blank, 0, false}
};

constexpr unsigned long INACTIVITY_DELAY = 30000;

constexpr unsigned long ZONE_STATE_CHANGE_DELAY = 1000;

GlobalState globalState = Inactive;

unsigned long lastGlobalStateChange = 0;

unsigned long lastActive = 0;

void loop() {
  unsigned long now = millis();

  // on allume le laser si on est pas en inactif
  digitalWrite(LASER, globalState == Inactive ? LOW : HIGH);

  if (now - lastJoystickRead >= JOYSTICK_INPUT_DELAY) {
    lastJoystickRead = now;

    // calcul du delta a appliquer aux moteurs
    int dx = analogRead(JOYSTICK_X) - 511;
    if (dx < 30 && dx > -30) {
      dx = 0;
    }
    dx = clamp(dx / 100, -1, 1);

    int dy = analogRead(JOYSTICK_Y) - 511;
    if (dy < 30 && dy > -30) {
      dy = 0;
    }
    dy = clamp(dy / 100, -1, 1)  * -1;

    int posX = servo1.read() + dx;
    if (posX > 83 && posX < 110) {
      servo1.write(servo1.read() + dx);
    }

    int posY = servo2.read() + dy;
    if(posY > 72 && posY < 108) {
      servo2.write(servo2.read() + dy);
    }

    // si le delta a appliquer est non nul
    if (dx != 0 || dy != 0) {
      if (globalState == Inactive) {
        globalState = Start;

        lastGlobalStateChange = now;
      }

      lastActive = now;
    }
  }

  // si l'utilisateur a interragi pour la dernière fois il y a plus de
  // INACTIVITY_DELAY secondes et qu'on est pas déjà en inactif, on passe en inactif.
  if (globalState != Inactive && now - lastActive > INACTIVITY_DELAY) {
    globalState = Inactive;

    for (int i = 0; i < NB_ZONES; i++) {
      zones[i].state = Blank;
      zones[i].lastStateChange = now;
    }

    lastGlobalStateChange = now;

    // remise à zéro des servos
    servo1.write(93);
    servo2.write(93);
  }

  // si on est en état "démarrage" depuis plus de 15 secondes,
  // on passe en "actif" (pour masquer la vidéo introductive).
  if (globalState == Start && now - lastGlobalStateChange > 15000) {
    globalState = Active;
    lastGlobalStateChange = now;
    lastActive = now;
  }

  // afficher l'état de l'activité au format suivant :

  // a,b,c,d,e
  //
  // avec :
  // a = état global de l'application
  // b,c,d,e = état de chaque zone

  Serial.print(globalState);

  Serial.print(',');

  for (int i = 0; i < NB_ZONES; i++) {
    Zone &zone = zones[i];

    int lumen = sensorRawToPhys(analogRead(zone.photo_cell_pin));

    // si la valeur mesurée en lumen est au delà de 2000, alors
    // le laser vient de passer sur le capteur
    if (lumen > 2000 && now - zone.lastStateChange > ZONE_STATE_CHANGE_DELAY) {
      zone.lastStateChange = now;

      // si la zone n'est pas découverte, on la passe en "scannée"
      if (zone.state == Blank) {
        zone.state = Scanned;
      // si la zone est déjà scannée et qu'elle est candidate
      // au replentage, on passe en "balisée"
      } else if (zone.isCandidate && zone.state == Scanned) {
        zone.state = Probed;
      }
    }

    if (i > 0) {
      Serial.print(',');
    }

    Serial.print(zone.state);
  }

  Serial.print("\n");
}
