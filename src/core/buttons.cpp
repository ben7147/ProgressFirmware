#include <Arduino.h>
#include "buttons.h"

const int prevPress = 38;
const int selPress  = 40;
const int nextPress = 39;

void initButtons() {
  pinMode(prevPress, INPUT_PULLUP);
  pinMode(selPress, INPUT_PULLUP);
  pinMode(nextPress, INPUT_PULLUP);
}

bool check(int pin) {
  return digitalRead(pin) == LOW;
}
