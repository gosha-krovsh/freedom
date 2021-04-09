#include "model.h"

Model::Model(const Schedule& schedule) :
  time_(Time(8, 30)),
  schedule_(schedule) {
  objects_ = {
      Object(Point(0, 8, 1), brick_image),
      Object(Point(0, 7, 1), brick_image),
      Object(Point(0, 6, 1), brick_image),
      Object(Point(0, 5, 1), brick_image),

      Object(Point(4, 8, 1), brick_image),
      Object(Point(4, 7, 1), brick_image),
      Object(Point(4, 6, 1), brick_image),
      Object(Point(4, 5, 1), brick_image),

      Object(Point(1, 8, 1), brick_image),
      Object(Point(2, 8, 1), brick_image),
      Object(Point(3, 8, 1), brick_image),

      Object(Point(1, 5, 1), brick_image),
      Object(Point(2, 5, 1), brick_image),
      Object(Point(3, 5, 1), brick_image),

      Object(Point(1, 5, 0), brick_image),
      Object(Point(2, 5, 0), brick_image),
      Object(Point(3, 5, 0), brick_image),
      Object(Point(1, 6, 0), brick_image),
      Object(Point(2, 6, 0), brick_image),
      Object(Point(3, 6, 0), brick_image),
      Object(Point(1, 7, 0), brick_image),
      Object(Point(2, 7, 0), brick_image),
      Object(Point(3, 7, 0), brick_image),
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

const Schedule& Model::GetSchedule() const {
  return schedule_;
}

Time& Model::GetTime() {
  return time_;
}

const Time& Model::GetTime() const {
  return time_;
}

