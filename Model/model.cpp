#include "model.h"
#include "image_manager.h"

Model::Model() {
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

  /// TODO: Parse bots from JSON
  // TODO: parse it from json
  std::vector<QuestNode> quest_nodes{
      QuestNode(0, "MyQuestNodeName", QuestNode::Type::kMoveToDestination,
                std::vector<QString>{"7", "9", "1"})
  };
  quests_.emplace_back(0, "MyQuestName", quest_nodes);
}

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

std::vector<Bot>& Model::GetBots() {
  return bots_;
}
