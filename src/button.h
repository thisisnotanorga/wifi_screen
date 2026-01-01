#pragma once
#include "button.cpp"
#include <Arduino.h>

void button_init(button &b, uint8_t pin);
bool button_pressed(button &b, unsigned long debounceMs = 50);