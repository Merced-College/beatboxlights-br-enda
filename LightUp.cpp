#include "LightUp.h"

LightUp::LightUp(const int pins[], int count)
  : _pins(pins), _count(count) {}

void LightUp::begin() {
  for (int i = 0; i < _count; i++) {
    pinMode(_pins[i], OUTPUT);
    digitalWrite(_pins[i], LOW);
  }
}

void LightUp::clear() {
  for (int i = 0; i < _count; i++)
    digitalWrite(_pins[i], LOW);
}

void LightUp::showLevel(int level) {
  if (level < 0) level = 0;
  if (level > _count) level = _count;

  for (int i = 0; i < _count; i++)
    digitalWrite(_pins[i], i < level ? HIGH : LOW);
}

void LightUp::flashAll(unsigned int ms) {
  for (int i = 0; i < _count; i++)
    digitalWrite(_pins[i], HIGH);

  delay(ms);

  for (int i = 0; i < _count; i++)
    digitalWrite(_pins[i], LOW);
}