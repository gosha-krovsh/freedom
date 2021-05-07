#ifndef MODEL_CONSTANTS_H_
#define MODEL_CONSTANTS_H_

#include <cmath>

namespace constants {
  const int kNumberOfViewDirections = 8;
  const double kEps = 1e-7;
  const int kSizeOfBlock = 140;
  const int kHP = 100;
  const int kAttack = 25;
  const double kSpeed = 0.05;
  const int kAttackCooldown = 40;
  const double kAttackRadius = 0.65;

  // Shift circle attack of Hero to forward
  // to avoid attacking bots which are behind Hero.
  const double kCoefficientForShiftingCircleAttack = 0.5;

  // All durations are measured in ticks
  const int kDurationOfOneAnimationFrame = 15;
  const int kDurationOfShaking = 10;

  const double kShakeAmplitude = 0.01;
  const double kDistanceToDetectBlock = 2 * kSpeed;

  // The opacity of the block, when it's considered transparent.
  const double kBlockOpacity = 0.1;
  const double kBotOpacity = 0.4;
  const double kBotOpacityDistance = 2;

  // Needed to make |DynamicObject| movement in Right/Left direction more
  // realistic in isometric view.
  const double kIsometricSpeedCoefficient = 1 / std::sqrt(3);

  // Needed to detect collision from correct side
  const double kOffsetForCollisionDetection = 0.15;
  // Needed to prevent getting stuck at the joints of the blocks
  const double kMaxSumOfDeltas = 2 * (1 - kOffsetForCollisionDetection * 2 / 3);

  const int kWindowWidth = 850;
  const int kWindowHeight = 500;
  const int kFPS = 60;

  const double kXConversationWindowMultiplier = 0.25;
  const double kYConversationWindowMultiplier = 0.65;
  const double kWidthConversationWindowMultiplier = 0.5;
  const double kHeightConversationWindowMultiplier = 0.3;

  const int kTicksInMinute = 300;

  const int kCountOfBots = 3;
}  // namespace constants

#endif  // MODEL_CONSTANTS_H_
