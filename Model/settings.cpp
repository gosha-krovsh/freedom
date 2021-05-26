#include <QDebug>
#include "settings.h"

int Settings::kVolume = constants::kInitVolume;
int Settings::kBlockSize = constants::kInitBlockSize;
int Settings::kFPS = constants::kInitFPS;

double Settings::GetSpeed() {
  return constants::kInitSpeed / GetFPSCoefficient();
}

int Settings::GetDurationOfOneAnimationFrame() {
  return constants::kInitDurationOfOneAnimationFrame * GetFPSCoefficient();
}

int Settings::GetDurationOfShaking() {
  return constants::kInitDurationOfShaking * GetFPSCoefficient();
}

int Settings::GetAttackCooldown() {
  return constants::kInitAttackCooldown * GetFPSCoefficient();
}

double Settings::GetFPSCoefficient() {
  return (static_cast<double>(kFPS) / constants::kInitFPS);
}

int Settings::GetDefaultSoundDuration() {
  return constants::kInitDefaultSoundDuration * GetFPSCoefficient();
}
