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
  AnimatedObject(QPixmap** image, State state) : current_image_(image),
                                                 state_(state) {}
  void Tick(int) {
    if (GetIndexOfCurrentFrame() >= images_[state_].size()) {
      counter_ = 0;
    }

    *current_image_ = images_[state_][GetIndexOfCurrentFrame()].get();

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
    return counter_ / constants::kDurationOfOneFrame;
  }

 private:
  int counter_{0};
  QPixmap** current_image_;
  std::map<State, std::vector<std::unique_ptr<QPixmap>>> images_;
  State state_;
};

#endif  // GAMEOBJECT_ANIMATED_OBJECT_H_
