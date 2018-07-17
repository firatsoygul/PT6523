#include <PT6523.h>

PT6523 lcd;

void setup() {
  lcd.begin(10, 130); // SlaveSelect pin, chip address.
  lcd.speed(250);     // Animation speed.
}

void loop() {
  lcd.sText("PT6523 LIBRARY FOR ARDUINO"); // Text scrolling.
}