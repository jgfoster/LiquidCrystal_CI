// modeled on https://github.com/jgfoster/Blink

#include <Arduino.h>
#include "HelloLCD.h"

#ifdef MOCK_PINS_COUNT
#define COLS 16
#define ROWS 2
#include <LiquidCrystal_CI.h>
LiquidCrystal_CI lcd(2,3,4,5,6,7);
#else
#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
#endif

void HelloLCD::setup() {
  delay(200);  // https://forum.arduino.cc/index.php?topic=600452.0
  lcd.begin(16,2);
  lcd.setCursor(0,0);
#ifdef MOCK_PINS_COUNT
  lcd.print("Testing");
#else
  lcd.print("Hello");
#endif
  lcd.setCursor(0,1);
  lcd.print("World!");
}

void HelloLCD::loop() {
}
