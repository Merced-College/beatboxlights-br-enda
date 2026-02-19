#ifndef LIGHT_UP_H
#define LIGHT_UP_H

#include <Arduino.h>

class LightUp {
private:
  const int* _pins;
  int _count;

public:
  LightUp(const int pins[], int count);

  void begin();
  void clear();
  void showLevel(int level);
  void flashAll(unsigned int ms);
};

#endif