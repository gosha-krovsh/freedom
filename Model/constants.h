#ifndef MODEL_CONSTANTS_H_
#define MODEL_CONSTANTS_H_

#include <cmath>
#include <limits>
#include <string>
#include <array>

namespace constants {
  const int kInitVolume = 50;
  const int kInitBlockSize = 200;
  const int kInitFPS = 60;
  const double kInitSpeed = 0.05;
  // All durations are measured in ticks
  const int kInitDurationOfOneAnimationFrame = 14;
  const int kInitDurationOfShaking = 10;
  const int kInitAttackCooldown = 40;
  const int kInitDefaultSoundDuration = 30;

  const int kNumberOfViewDirections = 8;
  const double kEps = 1e-7;
  const double kMaxBlockOffset = 0.15;
  const int kHP = 100;
  const int kBlockHP = kHP * 5;
  const int kPoliceHP = kHP * 10;
  const double kPoliceIllegalDetectionRadius = 4.;
  const double kStepForSearchingWall = 0.25;
  const int kAttack = 25;
  const double kAttackRadius = 0.65;
  const double kStartConversationRadius = 1.75;
  const char* const kPoliceClothesName{"police"};
  const char* const kPrisonerClothesName{"roba"};
  const char* const kEmptyClothesName{""};
  const std::array<const char*, 3> kClothes{kEmptyClothesName,
                                            kPrisonerClothesName,
                                            kPoliceClothesName};

  const double kDoorOpenOffset = -0.4;
  const int kHeroSpawnX = 35;
  const int kHeroSpawnY = 14;

  // To avoid going through the closed door.
  const double kDoorInteractingDistanceCoefficient = 0.9;

  // Shift circle attack of Hero to forward
  // to avoid attacking bots which are behind Hero.
  const double kCoefficientForShiftingCircleAttack = 0.5;

  const double kShakeAmplitude = 0.01;
  const double kDistanceToDetectBlock = 2 * kInitSpeed;

  // The opacity of the block, when it's considered transparent.
  const double kBlockOpacity = 0.1;
  const double kBotOpacity = 0.6;
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

  const double kXConversationWindowMultiplier = 0.25;
  const double kYConversationWindowMultiplier = 0.65;
  const double kWidthConversationWindowMultiplier = 0.5;
  const double kHeightConversationWindowMultiplier = 0.3;

  const int kTicksInMinute = 75;
  const double kXQuestTaskListWindowMultiplier = 0.74;
  const double kYQuestTaskListWindowMultiplier = 0.03;
  const double kWidthQuestTaskListWindowMultiplier = 0.25;
  const double kHeightQuestTaskListWindowMultiplier = 0.4;

  // ItemBar constants
  const int kMaxElementsInItemBar = 7;
  const int kBarPackDefaultCenteredX = kWindowWidth / 2;
  const int kBarPackDefaultY = 3 * kWindowHeight / 5;
  const int kBarPackDefaultWidth = 9 * kWindowWidth / 14;
  const int kBarPackDefaultHeight = 2 * kWindowHeight / 5;

  // StatusBar constants
  const int kStatusBarDefaultCenteredX = 100 * kWindowWidth / 850;
  const int kStatusBarDefaultY = kWindowHeight / 25;
  const int kStatusBarDefaultWidth = 160 * kWindowWidth / 850;
  const int kStatusBarDefaultHeight = 100 * kWindowHeight / 500;
  const int kStatusBarIconSize = 40;

  const int kCoeffitientForSpaceBetweenButtons = 25;
  const double kCoeffitientForIconSize = 0.8;

  const int kInfinity = std::numeric_limits<int>::max();
}  // namespace constants

#endif  // MODEL_CONSTANTS_H_
