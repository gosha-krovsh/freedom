#include "model.h"

Model::Model(const Schedule& schedule) :
    time_(Time(8, 30)),
    schedule_(schedule) {
  Wall::SetImage(std::make_shared<QPixmap>(":brick"));
  objects_ = {
      new Wall(Point(0, 8, 1)),
      new Wall(Point(0, 6, 1)),
      new Wall(Point(0, 5, 1)),

      new Wall(Point(4, 8, 1)),
      new Wall(Point(4, 7, 1)),
      new Wall(Point(4, 6, 1)),
      new Wall(Point(4, 5, 1)),

      new Wall(Point(1, 8, 1)),
      new Wall(Point(2, 8, 1)),
      new Wall(Point(3, 8, 1)),

      new Wall(Point(1, 5, 1)),
      new Wall(Point(2, 5, 1)),
      new Wall(Point(3, 8, 1)),

      new Wall(Point(1, 5, 0)),
      new Wall(Point(2, 5, 0)),
      new Wall(Point(3, 5, 0)),
      new Wall(Point(1, 6, 0)),
      new Wall(Point(2, 6, 0)),
      new Wall(Point(3, 6, 0)),
      new Wall(Point(1, 7, 0)),
      new Wall(Point(2, 7, 0)),
      new Wall(Point(3, 7, 0)),
  };
  map_ = GameMap(constants::kHeightOfMap,
                 std::vector<std::vector<Object*>>(constants::kDepthOfMap,
                 std::vector<Object*>(constants::kWidthOfMap,
                   nullptr)));

  for (auto& object : objects_) {
    map_[object->GetZ()][object->GetY()][object->GetX()] = object;
  }
}

const Model::GameMap& Model::GetMap() const {
  return map_;
}
std::vector<Object*>& Model::GetObjects() {
  return objects_;
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
  for (auto& object : objects_) {
    delete object;
  }
}
