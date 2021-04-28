#include "model.h"
#include "image_manager.h"

void Model::SetMap(std::unique_ptr<GameMap>&& game_map) {
  map_ = std::move(game_map);
}
void Model::SetSchedule(std::unique_ptr<Schedule>&& schedule) {
  schedule_ = std::move(schedule);
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
  return *schedule_;
}

Time& Model::GetTime() {
  return time_;
}

const Time& Model::GetTime() const {
  return time_;
}

std::weak_ptr<QPixmap> Model::GetImage(const QString& name) {
  return image_manager.GetImage(name);
}
