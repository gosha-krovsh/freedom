#ifndef MODEL_SETTINGS_H_
#define MODEL_SETTINGS_H_

#include "constants.h"

struct Settings {
  static int kVolume;
  static int kBlockSize;
  static int kFPS;
  static double GetSpeed();
  static int GetDurationOfOneAnimationFrame();
};

#endif  // MODEL_SETTINGS_H_
