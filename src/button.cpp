#include "button.h"


//creat button structure contains all the variables needed for button the button
struct button {
  uint8_t pin;
  bool physical_state;           // mostly pull up so HIGH = not pressed
  bool last_read;           // Last reading to check further if it changed
  unsigned long  lastChangeMs ; // timer debounce
};

void button_init(button &b, uint8_t pin) {
  b.pin = pin;
  pinMode(b.pin, INPUT_PULLUP);
  b.physical_state = HIGH; // état initial au repos
  b.last_read = HIGH;
  b.lastChangeMs = millis();
}


// true UNE seule fois au moment de l'appui (front)
bool button_pressed(button &b, unsigned long debounceMs) {
  bool reading = digitalRead(b.pin);

  if (reading != b.last_read) {
    b.last_read = reading;
    b.lastChangeMs = millis();
  }

  if (millis() - b.lastChangeMs >= debounceMs) {
    if (reading != b.physical_state) {
      b.physical_state = reading;

      // INPUT_PULLUP: appuyé = LOW
      if (b.physical_state == LOW) return true;
    }
  }

  return false;
}
