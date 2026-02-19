#include "BeatDetector.h"

BeatDetector::BeatDetector(int threshold, unsigned long cooldownMs)
  : _threshold(threshold), _cooldownMs(cooldownMs), _lastBeatTime(0) {}

bool BeatDetector::isBeat(int signal, unsigned long nowMs) {
  if (signal > _threshold && (nowMs - _lastBeatTime) > _cooldownMs) {
    _lastBeatTime = nowMs;
    return true;
  }
  return false;
}