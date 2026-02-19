#include "MicSensor.h"

MicSensor::MicSensor(int analogPin, int signalMin, int signalMax)
  : _pin(analogPin), _baseline(512), _signalMin(signalMin), _signalMax(signalMax) {}

int MicSensor::readRaw() {
  return analogRead(_pin);
}

int MicSensor::readSignal(int raw) {
  _baseline = (_baseline * 99L + raw) / 100L;
  int diff = raw - (int)_baseline;
  if (diff < 0) diff = -diff;
  return diff;
}

int MicSensor::levelFromSignal(int signal) const {
  if (signal <= _signalMin) return 0;
  if (signal >= _signalMax) return 5;

  long scaled = (long)(signal - _signalMin) * 5L;
  long range = (long)(_signalMax - _signalMin);
  return scaled / range;
}

long MicSensor::getBaseline() const {
  return _baseline;
}
