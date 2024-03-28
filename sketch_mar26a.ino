#include <Servo.h>

constexpr uint8_t JOYSTICK_X = A5;
constexpr uint8_t JOYSTICK_Y = A4;

#define VIN 5 // V power voltage
#define R 10000 //ohm resistance value

#define LASER 12

Servo servo1;
#define SERVO1 5

Servo servo2;
#define SERVO2 6

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

template <typename T>
T clamp(T value, T min, T max) {
  if (value < min) {
    return min;
  } else if (value > max) {
    return max;
  } else {
    return value;
  }
}

unsigned long lastTime = 0;

constexpr unsigned long JOYSTICK_INPUT_DELAY = 75;

enum GlobalState {
  Inactive,
  Start,
  Active,
};

enum ZoneState {
  Blank,
  Scanned,
  Probed
};

struct Zone {
  uint8_t photo_cell_pin;

  ZoneState state;

  unsigned long lastStateChange;

  bool isCandidate;
};

#define NB_ZONES 4

Zone zones[NB_ZONES] = {
  {A0, Blank, 0, true},
  {A1, Blank, 0, false},
  {A2, Blank, 0, true},
  {A3, Blank, 0, false}
};

constexpr unsigned long INACTIVITY_DELAY = 30000;

GlobalState globalState = Inactive;

unsigned long lastGlobalStateChange = 0;

unsigned long lastActive = 0;

void loop() {
  unsigned long now = millis();

  digitalWrite(LASER, globalState == Inactive ? LOW : HIGH);

  if (now - lastTime >= JOYSTICK_INPUT_DELAY) {
    lastTime = now;

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

    if (dx != 0 || dy != 0) {
      if (globalState == Inactive) {
        globalState = Start;

        lastGlobalStateChange = now;
      }

      lastActive = now;
    }
  }

  if (globalState != Inactive && now - lastActive > INACTIVITY_DELAY) {
    globalState = Inactive;

    for (int i = 0; i < NB_ZONES; i++) {
      zones[i].state = Blank;
      zones[i].lastStateChange = now;
    }

    lastGlobalStateChange = now;

    servo1.write(93);
    servo2.write(93);
  }

  constexpr unsigned long ZONE_STATE_CHANGE_DELAY = 1000;

  if (globalState == Start && now - lastGlobalStateChange > 15000) {
    globalState = Active;
    lastGlobalStateChange = now;
    lastActive = now;
  }

  Serial.print(globalState);

  Serial.print(',');

  for (int i = 0; i < NB_ZONES; i++) {
    Zone &zone = zones[i];

    int lumen = sensorRawToPhys(analogRead(zone.photo_cell_pin));

    if (lumen > 2000 && now - zone.lastStateChange > ZONE_STATE_CHANGE_DELAY) {
      zone.lastStateChange = now;

      if (zone.state == Blank) {
        zone.state = Scanned;
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