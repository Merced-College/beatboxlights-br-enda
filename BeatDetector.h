#ifndef BEAT_DETECTOR_H
#define BEAT_DETECTOR_H

#include <Arduino.h>

class BeatDetector {
private:
  int _threshold;
  unsigned long _cooldownMs;
  unsigned long _lastBeatTime;

public:
  BeatDetector(int threshold, unsigned long cooldownMs);
  bool isBeat(int signal, unsigned long nowMs);
};

#endif