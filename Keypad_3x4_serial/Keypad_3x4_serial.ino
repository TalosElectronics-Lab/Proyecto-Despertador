/*
 * Rafael Lozano rolon
 * soporte@taloselectronics.com
*/
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns

char keys[ROWS][COLS] = {
  {1, 2, 3},
  {4, 5, 6},
  {7, 8, 9},
  {'*', 'z', '#'}
};

byte rowPins[ROWS] = {7, 2, 3, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 8, 4}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
}

void loop() {

  char key = keypad.getKey();
  if (key) 
  {
    Serial.println(key);
  }
}
