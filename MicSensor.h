#ifndef MIC_SENSOR_H
#define MIC_SENSOR_H

#include <Arduino.h>

class MicSensor {
private:
  int _pin;
  long _baseline;
  int _signalMin;
  int _signalMax;

public:
  MicSensor(int analogPin, int signalMin, int signalMax);

  int readRaw();
  int readSignal(int raw);
  int levelFromSignal(int signal) const;
  long getBaseline() const;
};

#endif