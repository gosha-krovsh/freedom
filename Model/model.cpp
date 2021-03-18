#include "model.h"

Model::Model() {
  objects_ = {
      Object(Point(0, 5, 0), QPixmap(":brick.png")),
      Object(Point(1, 5, 0), QPixmap(":brick.png")),
      Object(Point(2, 5, 0), QPixmap(":brick.png")),
      Object(Point(0, 6, 0), QPixmap(":brick.png")),
      Object(Point(1, 6, 0), QPixmap(":brick.png")),
      Object(Point(2, 6, 0), QPixmap(":brick.png")),
      Object(Point(0, 7, 0), QPixmap(":brick.png")),
      Object(Point(1, 7, 0), QPixmap(":brick.png")),
      Object(Point(2, 7, 0), QPixmap(":brick.png"))
  };
  map_ = GameMap(constants::kHeightOfMap,
                 std::vector<std::vector<Object*>>(constants::kDepthOfMap,
                 std::vector<Object*>(constants::kWidthOfMap,
                   nullptr)));

  for (auto& object : objects_) {
    map_[object.GetZ()][object.GetY()][object.GetX()] = &object;
  }
}

const Model::GameMap& Model::GetMap() const {
  return map_;
}

const Hero& Model::GetHero() const {
  return hero_;
}
Hero& Model::GetHero() {
  return hero_;
}

