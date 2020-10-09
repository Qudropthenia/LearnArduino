#include <FastLED.h>

#define DI_PIN 13
#define NUM_LEDS 13
//#define BRIGHT 20

struct RGB {
  byte r = 0;
  byte g = 0;
  byte b = 0;
} style;
// Храним считанные данные
String incStr = "";
CRGB leds[NUM_LEDS];  // создаём ленту
byte BRIGHT = 0;

void setup() {
  Serial.begin(9600);
  // Инициализация светодиодов
  FastLED.addLeds<WS2812, DI_PIN, GRB>(leds, NUM_LEDS);
  // Яркость светодиодов
  FastLED.setBrightness(BRIGHT);
}

void loop() {
  if (Serial.available() > 0) {
    incStr = Serial.readString();
    parseStrToRGB();
    returnRGBInfo();
    showColor();
    clearData();
  }
}

void parseStrToRGB() {
  int size_s = strlen(incStr.c_str()) - 1;
  String buff;
  int index = 0;

  for (int i = 0; i <= size_s; i++) {
    if (incStr[i] != ',' && i < size_s) {
      buff += incStr[i];
    } else {
      byte value = (byte) buff.toInt();
      switch (index) {
        case 0: style.r = value; break;
        case 1: style.g = value; break;
        case 2: style.b = value; break;
        case 3: BRIGHT = value; break;
      }
      buff = "";
      index++;
    }
  }
}

void returnRGBInfo() {
  Serial.println("R: " + String(style.r));
  Serial.println("G: " + String(style.g));
  Serial.println("B: " + String(style.b));
}

void showColor() {
  int r = (int) style.r;
  int g = (int) style.g;
  int b = (int) style.b;

  LEDS.showColor(CRGB(r, g, b));
  FastLED.setBrightness(BRIGHT);
  //LEDS.showColor(CRGB(255, 0, 0));
}

void clearData() {
  style.r = 0;
  style.g = 0;
  style.b = 0;
  incStr = "";
}
