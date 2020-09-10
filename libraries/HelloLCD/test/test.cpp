#include <Arduino.h>
#include <ArduinoUnitTests.h>
#include <LiquidCrystal_CI.h>
#include "HelloLCD.h"

unittest(hello)
{
    HelloLCD helloLCD;
    LiquidCrystal_CI* lcd = LiquidCrystal_CI::forRsPin(2);
    assertNotNull(lcd);
    assertEqual(1, lcd->getRows());
    helloLCD.setup();
    assertEqual(2, lcd->getRows());
}

unittest_main()
