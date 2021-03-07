#include "model.h"

Model::Model() {
  map_ = Map(constants::kHeightOfMap,
             Layer(constants::kDepthOfMap,
                   Line(constants::kWidthOfMap,
                        nullptr)));

  for (auto& object : objects_) {
    map_[object.GetZ()][object.GetY()][object.GetX()] = &object;
  }
}

const std::vector<std::vector<std::vector<Object*>>>& Model::GetMap() const {
  return map_;
}

const Hero& Model::GetHero() const {
  return hero_;
}
Hero& Model::GetHero() {
  return hero_;
}

