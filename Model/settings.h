#ifndef MODEL_SETTINGS_H_
#define MODEL_SETTINGS_H_

#include "constants.h"

struct Settings {
  static int kVolume;
  static int kBlockSize;
  static int kFPS;
  static double GetSpeed();
  static int GetDurationOfOneAnimationFrame();
  static int GetDurationOfShaking();
  static int GetAttackCooldown();
  static int GetDefaultSoundDuration();

 private:
  static double GetFPSCoefficient();
};

#endif  // MODEL_SETTINGS_H_
