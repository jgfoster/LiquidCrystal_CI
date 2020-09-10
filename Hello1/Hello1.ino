// modeled on https://www.arduino.cc/en/Tutorial/HelloWorld

#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() { 
    delay(200);  // https://forum.arduino.cc/index.php?topic=600452.0
    lcd.begin(16,2);
    lcd.setCursor(0,0);
    lcd.print("Hello sketch!");
 }
void loop() {
    lcd.setCursor(0,1);
    lcd.print(millis() / 1000);
}
