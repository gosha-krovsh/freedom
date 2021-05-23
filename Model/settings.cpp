#include "settings.h"

int Settings::kVolume = constants::kInitVolume;
int Settings::kBlockSize = constants::kInitBlockSize;
int Settings::kFPS = constants::kInitFPS;

double Settings::GetSpeed() {
  return constants::kInitSpeed * kFPS / constants::kInitFPS;
}
