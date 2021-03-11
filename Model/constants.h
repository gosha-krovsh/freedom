#ifndef MODEL_CONSTANTS_H_
#define MODEL_CONSTANTS_H_

#include <cmath>

namespace constants {
  const int kSizeOfBlock = 140;
  const int kHP = 100;
  const double kSpeed = 0.05;

  // Needed to make |Hero| movement in Right/Left direction more realistic, in
  // isometric view.
  const double kHorizontalSpeedMultiplier = 1 / std::sqrt(3);

  const int kHeightOfMap = 2;
  const int kDepthOfMap = 10;
  const int kWidthOfMap = 10;

  const int kWindowWidth = 850;
  const int kWindowHeight = 500;
  const int kFPS = 60;
}  // namespace constants

#endif  // MODEL_CONSTANTS_H_
