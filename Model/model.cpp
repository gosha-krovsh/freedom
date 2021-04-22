#include "model.h"
#include "image_manager.h"

Model::Model(const Schedule& schedule,
             std::unique_ptr<GameMap> game_map) :
    time_(Time(8, 30)),
    schedule_(schedule),
    map_(std::move(game_map)) {}

Model::~Model() {
  ImageManager::Wipe();
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

const Schedule& Model::GetSchedule() const {
  return schedule_;
}

Time& Model::GetTime() {
  return time_;
}

const Time& Model::GetTime() const {
  return time_;
}
