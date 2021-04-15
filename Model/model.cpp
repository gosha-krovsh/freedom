#include "model.h"

Model::Model() {
  // This part is also deprecated, will be updated after merge with master
  objects_ = {
      new Object(Point(0, 8, 1), QPixmap(":brick.png")),
      new Object(Point(0, 7, 1), QPixmap(":brick.png")),
      new Object(Point(0, 6, 1), QPixmap(":brick.png")),
      new Object(Point(0, 5, 1), QPixmap(":brick.png")),

      new Object(Point(4, 8, 1), QPixmap(":brick.png")),
      new Object(Point(4, 7, 1), QPixmap(":brick.png")),
      new Object(Point(4, 6, 1), QPixmap(":brick.png")),
      new Object(Point(4, 5, 1), QPixmap(":brick.png")),

      new Object(Point(1, 8, 1), QPixmap(":brick.png")),
      new Object(Point(2, 8, 1), QPixmap(":brick.png")),
      new Object(Point(3, 8, 1), QPixmap(":brick.png")),

      new Object(Point(1, 5, 1), QPixmap(":brick.png")),
      new Object(Point(3, 5, 1), QPixmap(":brick.png")),
      new Chest(Point(3, 6, 1), QPixmap(":brick.png"), {
                Item("YaBlock1", 1, QPixmap(":brick.png")),
                Item("YaBlock2", 2, QPixmap(":brick.png")),
                Item("YaBlock3", 3, QPixmap(":brick.png"))}),

      new Object(Point(1, 5, 0), QPixmap(":brick.png")),
      new Object(Point(2, 5, 0), QPixmap(":brick.png")),
      new Object(Point(3, 5, 0), QPixmap(":brick.png")),
      new Object(Point(1, 6, 0), QPixmap(":brick.png")),
      new Object(Point(2, 6, 0), QPixmap(":brick.png")),
      new Object(Point(3, 6, 0), QPixmap(":brick.png")),
      new Object(Point(1, 7, 0), QPixmap(":brick.png")),
      new Object(Point(2, 7, 0), QPixmap(":brick.png")),
      new Object(Point(3, 7, 0), QPixmap(":brick.png")),
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

const Hero& Model::GetHero() const {
  return hero_;
}
Hero& Model::GetHero() {
  return hero_;
}

