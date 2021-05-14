#include "model.h"
#include "image_manager.h"

Model::Model() {
  // TODO: Parse bots from JSON
  bots_.emplace_back("Hero", Point(4, 1, 1),
                     std::vector<Point>(
                         {Point(4, 6, 1),
                          Point(1, 6, 1),
                          Point(1, 1, 1),
                          Point(4, 1, 1),
                          Point(4, 6, 1),
                          Point(2, 6, 1),
                          Point(2, 9, 1),
                          Point(7, 9, 1)}));
}

void Model::SetMap(std::unique_ptr<GameMap>&& game_map) {
  map_ = std::move(game_map);
}
void Model::SetSchedule(std::unique_ptr<Schedule>&& schedule) {
  schedule_ = std::move(schedule);
}

void Model::SetConversations(
    std::vector<std::shared_ptr<Conversation>>&& conversations) {
  conversations_ = std::move(conversations);
  bots_.at(0).SetCurrentConversation(conversations_[0]);
}

void Model::SetQuests(std::vector<Quest>&& quests) {
  quests_ = std::move(quests);
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

std::vector<Bot>& Model::GetBots() {
  return bots_;
}
const std::vector<Bot>& Model::GetBots() const {
  return bots_;
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

const Quest& Model::GetQuestById(int id) const {
  if (id < 0 || id >= quests_.size()) {
    qDebug() << "Invalid quest id";
  }
  return quests_[id];
}

const std::vector<Quest>& Model::GetCurrentQuests() const {
  return current_quests_;
}

std::vector<Quest>& Model::GetCurrentQuests() {
  return current_quests_;
}

void Model::DeleteFightingPairWithIndex(int index) {
  fighting_pairs_.erase(fighting_pairs_.begin() + index);
}
