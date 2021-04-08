#ifndef GAMEOBJECT_ANIMATOR_H_
#define GAMEOBJECT_ANIMATOR_H_

#include <QPixmap>

#include <memory>
#include <string>
#include <vector>
#include <map>

#include "Model/constants.h"

template<class State>
class Animator {
 public:
  explicit Animator(const State& state) : state_(state) {}
  void Tick(int) {
    counter_++;

    if (GetIndexOfCurrentFrame() >= images_[state_].size()) {
      counter_ = 0;
    }
  }

  void AssignStateToAnimation(State state, const std::vector<QString>& names) {
    for (const auto& name : names) {
      images_[state].push_back(std::make_shared<QPixmap>(":" + name + ".png"));
    }
  }

  std::shared_ptr<QPixmap> GetImageByState(const State& state) {
    if (state_ != state) {
      state_ = state;
      counter_ = 0;
    }
    return images_[state_][GetIndexOfCurrentFrame()];
  }

 private:
  int GetIndexOfCurrentFrame() {
    return counter_ / constants::kDurationOfOneAnimationFrameInTicks;
  }

 private:
  int counter_{0};
  std::map<State, std::vector<std::shared_ptr<QPixmap>>> images_;
  State state_;
};

#endif  // GAMEOBJECT_ANIMATOR_H_
