#ifndef SOUND_DEVICE_H
#define SOUND_DEVICE_H

#include <Arduino.h>

class SoundDevice {
private:
  int _pin;

public:
  SoundDevice(int pin);
  void begin();
  void playBeatClick(int intensityLevel);
};

#endif