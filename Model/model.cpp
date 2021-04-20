#include "model.h"

Model::Model(const Schedule& schedule) :
    time_(Time(8, 30)),
    schedule_(schedule) {
  Wall::SetImage(std::make_shared<QPixmap>(":brick"));
  std::vector<Point> wall_coords = {
      Point(0, 8, 1),
      Point(0, 6, 1),
      Point(0, 5, 1),

      Point(4, 8, 1),
      Point(4, 7, 1),
      Point(4, 6, 1),
      Point(4, 5, 1),

      Point(1, 8, 1),
      Point(2, 8, 1),
      Point(3, 8, 1),

      Point(1, 5, 1),
      Point(2, 5, 1),
      Point(3, 8, 1),

      Point(1, 5, 0),
      Point(2, 5, 0),
      Point(3, 5, 0),
      Point(1, 6, 0),
      Point(2, 6, 0),
      Point(3, 6, 0),
      Point(1, 7, 0),
      Point(2, 7, 0),
      Point(3, 7, 0),
  };
  map_ = GameMap(constants::kHeightOfMap,
                 std::vector<std::vector<Object*>>(constants::kDepthOfMap,
                 std::vector<Object*>(constants::kWidthOfMap,
                   nullptr)));

  for (const auto& coords : wall_coords) {
    map_[coords.z][coords.y][coords.x] = new Wall(coords);
  }
}

const Model::GameMap& Model::GetMap() const {
  return map_;
}
Model::GameMap& Model::GetMap() {
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

Model::~Model() {
  Wall::DeleteImage();

  for (auto& plane : map_) {
    for (auto& line : plane) {
      for (auto& block : line) {
        delete block;
      }
    }
  }
}
