#include "SoundDevice.h"

SoundDevice::SoundDevice(int pin) : _pin(pin) {}

void SoundDevice::begin() {
  pinMode(_pin, OUTPUT);
}

void SoundDevice::playBeatClick(int intensityLevel) {
  if (intensityLevel < 0) intensityLevel = 0;
  if (intensityLevel > 5) intensityLevel = 5;

  int freq = 600 + intensityLevel * 120;
  int dur  = 25 + intensityLevel * 10;

  tone(_pin, freq, dur);
  delay(dur + 5);
  noTone(_pin);
}
