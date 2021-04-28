#include "model.h"

Model::Model(const Schedule& schedule,
             std::unique_ptr<GameMap> game_map) :
    time_(Time(8, 30)),
    schedule_(schedule),
    map_(std::move(game_map)) {
  // Temp code for adding bots
  bots_.emplace_back(Point(2, 2, 1), "Hero", 100);
}

const GameMap& Model::GetMap() const {
  return *map_;
}

void Model::CreateFightingPair(Creature* first, Creature* second) {
  fighting_pairs_.emplace_back(first, second);
}
std::pair<Creature*, Creature*> Model::GetFightingPairWithIndex(int index) {
  return fighting_pairs_.at(index);
}

int Model::GetNumberOfFightingPairs() const {
  return fighting_pairs_.size();
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

Model::~Model() {
  Wall::DeleteImage();
}
void Model::DeleteFightingPair(const std::pair<Creature*, Creature*>& pair) {
  auto iter = std::find(fighting_pairs_.begin(), fighting_pairs_.end(), pair);
  if (iter != fighting_pairs_.end()) {
    fighting_pairs_.erase(iter);
  }
}

// Temp code for adding bots
std::vector<Creature>& Model::GetBots() {
  return bots_;
}
