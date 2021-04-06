#ifndef GAMEOBJECT_ANIMATED_OBJECT_H_
#define GAMEOBJECT_ANIMATED_OBJECT_H_

#include <QPixmap>

#include <memory>
#include <string>
#include <vector>
#include <map>

#include "Model/constants.h"

template<class State>
class AnimatedObject {
 public:
  explicit AnimatedObject(State state) : state_(state) {}
  void Tick(int) {
    if (GetIndexOfCurrentFrame() >= images_[state_].size()) {
      counter_ = 0;
    }

    SetImage(images_[state_][GetIndexOfCurrentFrame()]);

    counter_++;
  }

  void SetStateForAnimation(const State& state) {
    if (state_ != state) {
      state_ = state;
      counter_ = 0;
    }
  }

  void AssignStateToAnimation(State state, const std::vector<QString>& names) {
    for (const auto& name : names) {
      images_[state].push_back(std::make_unique<QPixmap>(":" + name + ".png"));
    }
  }

 private:
  int GetIndexOfCurrentFrame() {
    return counter_ / constants::kDurationOfOneAnimationFrameInTicks;
  }
  virtual void SetImage(std::shared_ptr<QPixmap> new_image) = 0;

 private:
  int counter_{0};
  std::map<State, std::vector<std::shared_ptr<QPixmap>>> images_;
  State state_;
};

#endif  // GAMEOBJECT_ANIMATED_OBJECT_H_
