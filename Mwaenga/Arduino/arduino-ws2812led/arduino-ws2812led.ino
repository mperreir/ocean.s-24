#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif


// 定义 LEDStrip 结构体
struct LEDStrip {
  int pin;
  int numLEDs;
  Adafruit_NeoPixel strip;
};

// 初始化 Adafruit_NeoPixel 对象的函数
void initNeoPixel(Adafruit_NeoPixel &strip, int pin, int numLEDs) {
  strip = Adafruit_NeoPixel(numLEDs, pin, NEO_GRB + NEO_KHZ800);
  strip.begin();
  strip.show();
}

// 初始化 LEDStrip 数组的函数
void initLEDStrips(LEDStrip *strips, int numStrips) {
  for (int i = 0; i < numStrips; i++) {
    initNeoPixel(strips[i].strip, strips[i].pin, strips[i].numLEDs);
  }
}

const int numStrips = 5;
LEDStrip myLEDStrips[numStrips] = {
  {6, 200},
  {5, 200},
  {4, 200},
  {3, 200},
  {2,200}
};

void setup() {
  Serial.begin(9600);
  initLEDStrips(myLEDStrips, numStrips);
}

void clear() {
  for (int i = 0; i < numStrips; i++) {
    myLEDStrips[i].strip.clear();
    myLEDStrips[i].strip.show();
  }
}

void level(int level) {
  clear();
  for (int i = 0; i < level; i++) {
    myLEDStrips[i].strip.clear();
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
    myLEDStrips[i].strip.clear();
    for (int j = 0; j < myLEDStrips[i].numLEDs; j++) {
      myLEDStrips[i].strip.setPixelColor(j, myLEDStrips[i].strip.Color(35, 50, 5));
    }
    myLEDStrips[i].strip.show();
  }
}

void step(int s) {
  if ( s == 0)
  {
    clear();
  } else if (s > 0 && s <= 3) {
    level(s+2);
  } else{
    clear();
  }
}

void loop() {
  if (Serial.available() > 0) {
    char s = Serial.read();
    if (s != 'N' && s!= 'S') {
      step(s - '0');
  }
}
}
