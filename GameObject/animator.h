#ifndef GAMEOBJECT_ANIMATOR_H_
#define GAMEOBJECT_ANIMATOR_H_

#include <QPixmap>

#include <memory>
#include <string>
#include <vector>
#include <map>

#include "Model/constants.h"
#include "Model/settings.h"

template<class State>
class Animator {
 public:
  explicit Animator(const State& state) : state_(state) {}
  void Tick();
  void AssignStateToAnimation(State state, const std::vector<QString>& names);

  std::shared_ptr<QPixmap> GetImageByState(const State& state);

 private:
  void CheckCorrectIndex();
  int GetIndexOfCurrentFrame() const;

 private:
  int counter_{0};
  std::map<State, std::vector<std::shared_ptr<QPixmap>>> images_;
  State state_;
};

template<class State>
void Animator<State>::CheckCorrectIndex() {
  if (GetIndexOfCurrentFrame() >= images_[state_].size()) {
    counter_ = 0;
  }
}
template<class State>
void Animator<State>::Tick() {
  ++counter_;
  CheckCorrectIndex();
}

template<class State>
void Animator<State>::
    AssignStateToAnimation(State state, const std::vector<QString>& names) {
  images_[state].reserve(names.size());
  for (const auto& name : names) {
    images_[state].emplace_back(std::make_shared<QPixmap>(":" + name + ".png"));
  }
}

template<class State>
std::shared_ptr<QPixmap> Animator<State>::GetImageByState(const State& state) {
  if (state_ != state) {
    state_ = state;
    counter_ = 0;
  }
  CheckCorrectIndex();
  return images_.at(state_).at(GetIndexOfCurrentFrame());
}

template<class State>
int Animator<State>::GetIndexOfCurrentFrame() const {
  return counter_ / Settings::GetDurationOfOneAnimationFrame();
}

#endif  // GAMEOBJECT_ANIMATOR_H_
