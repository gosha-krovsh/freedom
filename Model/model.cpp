#include "model.h"

Model::Model(const Schedule& schedule,
             std::unique_ptr<GameMap> game_map) :
    time_(Time(8, 30)),
    schedule_(schedule),
    map_(std::move(game_map)) {
    bots_.emplace_back(std::make_unique<Bot>("Hero", Point(4, 1, 1), 0));
    bots_.emplace_back(std::make_unique<Bot>("Hero", Point(1, 8, 1), 4));
}

const GameMap& Model::GetMap() const {
  return *map_;
}

GameMap& Model::GetMap() {
  return *map_;
}

const Hero& Model::GetHero() const {
  return hero_;
}
Hero& Model::GetHero() {
  return hero_;
}
const std::vector<std::unique_ptr<Bot>>& Model::GetBots() const {
  return bots_;
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

