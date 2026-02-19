//Brenda Romero
//CPSC-25-12703
//02/19/26

/*
  BeatBoxLights.ino
  Beat Box Lights - Advanced C++ Embedded Systems Lab

  Listens to microphone on A0, estimates intensity, shows a 5-LED level meter,
  detects beats (threshold + cooldown), and plays a click on a piezo.

  Uses a fixed-size history buffer (no std::vector) so it compiles on Arduino Uno.
*/

#include <Arduino.h>
#include "MicSensor.h"
#include "LightUp.h"
#include "BeatDetector.h"
#include "SoundDevice.h"

// -------------------- Pin / parameter configuration --------------------
static const int MIC_PIN = A0;
static const int LED_PINS[5] = { 9, 10, 11, 12, 13 };
static const int PIEZO_PIN = 6;

static const int SIGNAL_MIN      = -4;
static const int SIGNAL_MAX      = 190;
static const int BEAT_THRESHOLD  = 67;
static const unsigned long COOLDOWN_MS = 180;

// -------------------- Objects --------------------
MicSensor mic(MIC_PIN, SIGNAL_MIN, SIGNAL_MAX);
LightUp lights(LED_PINS, 5);
BeatDetector detector(BEAT_THRESHOLD, COOLDOWN_MS);
SoundDevice sound(PIEZO_PIN);

// -------------------- Smoothing (fixed-size history buffer) --------------------
static const size_t MAX_LEVEL_HISTORY = 15;
static int levelHistory[MAX_LEVEL_HISTORY];
static size_t levelCount = 0;

// Adds a level to the history.
// If full, shifts left by one (oldest dropped) and appends newest.
void pushLevel(int level) {
  if (levelCount < MAX_LEVEL_HISTORY) {
    levelHistory[levelCount] = level;
    levelCount++;
  } else {
    // Shift everything left to remove the oldest entry
    for (size_t i = 1; i < MAX_LEVEL_HISTORY; i++) {
      levelHistory[i - 1] = levelHistory[i];
    }
    levelHistory[MAX_LEVEL_HISTORY - 1] = level;
  }
}

// Returns the average of the stored levels.
int smoothLevel() {
  if (levelCount == 0) return 0;

  long sum = 0;
  for (size_t i = 0; i < levelCount; i++) {
    sum += levelHistory[i];
  }
  return (int)(sum / (long)levelCount);
}

void setup() {
  Serial.begin(9600);

  lights.begin();
  sound.begin();

  // Initialize history to zeros (not required, but nice and predictable)
  for (size_t i = 0; i < MAX_LEVEL_HISTORY; i++) {
    levelHistory[i] = 0;
  }
  levelCount = 0;

  Serial.println("BeatBoxLights starting...");
}

void loop() {
  // 1) Read microphone and compute signal intensity
  int raw = mic.readRaw();
  int signal = mic.readSignal(raw);
  int level = mic.levelFromSignal(signal);

  // 2) Store level and show smoothed LED meter
  pushLevel(level);
  int smoothed = smoothLevel();
  lights.showLevel(smoothed);

  // Optional: debug prints (comment out once tuned)
  // Serial.print("raw=");
  // Serial.print(raw);
  // Serial.print(" baseline=");
  // Serial.print(mic.getBaseline());
  // Serial.print(" signal=");
  // Serial.print(signal);
  // Serial.print(" level=");
  // Serial.print(level);
  // Serial.print(" smooth=");
  // Serial.println(smoothed);

  // 3) Beat detection + output effects
  if (detector.isBeat(signal, millis())) {
    sound.playBeatClick(level);  // click pitch changes with intensity
    lights.flashAll(30);         // quick flash for beat
  }

  delay(10);
}
