#include "model.h"

Model::Model(const Schedule& schedule, const GameMap& game_map) :
    time_(Time(8, 30)),
    schedule_(schedule),
    map_(game_map) {
  // objects_.insert(objects_.end(), {
  //     // The floor is white. It's easier to orientate in space then.
  //     Object(Point(0, 5, 1), brick_image),
  //     Object(Point(0, 6, 1), brick_image),
  //     Object(Point(0, 7, 1), brick_image),
  //     Object(Point(0, 8, 1), brick_image),
  //     Object(Point(0, 9, 1), brick_image),
  //     Object(Point(0, 10, 1), brick_image),
  //     Object(Point(0, 11, 1), brick_image),
  //     Object(Point(0, 12, 1), brick_image),
  //     Object(Point(0, 13, 1), brick_image),
  //     Object(Point(0, 14, 1), brick_image),
  //
  //     Object(Point(5, 5, 1), brick_image),
  //     Object(Point(5, 6, 1), brick_image),
  //     Object(Point(5, 7, 1), brick_image),
  //     Object(Point(5, 8, 1), brick_image),
  //     Object(Point(5, 9, 1), brick_image),
  //     Object(Point(5, 10, 1),brick_image),
  //     Object(Point(5, 11, 1), brick_image),
  //     // Object(Point(5, 12, 1), brick_image),
  //     Object(Point(5, 13, 1), brick_image),
  //     Object(Point(5, 14, 1), brick_image),
  //
  //
  //     Object(Point(1, 5, 1), brick_image),
  //     Object(Point(2, 5, 1), brick_image),
  //     Object(Point(3, 5, 1), brick_image),
  //     Object(Point(4, 5, 1), brick_image),
  //
  //     Object(Point(1, 9, 1), brick_image),
  //     Object(Point(2, 9, 1), brick_image),
  //     // Object(Point(3, 9, 1), brick_image),
  //     Object(Point(4, 9, 1), brick_image),
  //
  //     Object(Point(1, 14, 1), brick_image),
  //     Object(Point(2, 14, 1), brick_image),
  //     Object(Point(3, 14, 1), brick_image),
  //     Object(Point(4, 14, 1), brick_image),
  //
  //     Object(Point(2, 12, 1), brick_image),
  //     Object(Point(4, 8, 1), brick_image),
  //
  //     // ----------------------------------------------------
  //
  //     Object(Point(0, 5, 2), brick_image),
  //     Object(Point(0, 6, 2), brick_image),
  //     Object(Point(0, 7, 2), brick_image),
  //     Object(Point(0, 8, 2), brick_image),
  //     Object(Point(0, 9, 2), brick_image),
  //     Object(Point(0, 10, 2), brick_image),
  //     Object(Point(0, 11, 2), brick_image),
  //     Object(Point(0, 12, 2), brick_image),
  //     Object(Point(0, 13, 2), brick_image),
  //     Object(Point(0, 14, 2), brick_image),
  //
  //     Object(Point(5, 5, 2), brick_image),
  //     Object(Point(5, 6, 2), brick_image),
  //     Object(Point(5, 7, 2), brick_image),
  //     Object(Point(5, 8, 2), brick_image),
  //     Object(Point(5, 9, 2), brick_image),
  //     Object(Point(5, 10, 2), brick_image),
  //     Object(Point(5, 11, 2), brick_image),
  //     // Object(Point(5, 12, 1), brick_image),
  //     Object(Point(5, 13, 2), brick_image),
  //     Object(Point(5, 14, 2), brick_image),
  //
  //
  //     Object(Point(1, 5, 2), brick_image),
  //     Object(Point(2, 5, 2), brick_image),
  //     Object(Point(3, 5, 2), brick_image),
  //     Object(Point(4, 5, 2), brick_image),
  //
  //     Object(Point(1, 9, 2), brick_image),
  //     Object(Point(2, 9, 2), brick_image),
  //     // Object(Point(3, 9, 1), brick_image),
  //     Object(Point(4, 9, 2), brick_image),
  //
  //     Object(Point(1, 14, 2), brick_image),
  //     Object(Point(2, 14, 2), brick_image),
  //     Object(Point(3, 14, 2), brick_image),
  //     Object(Point(4, 14, 2), brick_image),
  //
  //     Object(Point(2, 12, 2), brick_image),
  //     Object(Point(4, 8, 2), brick_image),
  // });
  //
  // map_ = GameMap(&objects_, hero_.GetRoundedZ());
}

const GameMap& Model::GetMap() const {
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

