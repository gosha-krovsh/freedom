#include "model.h"
#include "image_manager.h"

Model::Model() {
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

void Model::SetConversations(std::vector<Conversation>&& conversations) {
  conversations_ = std::move(conversations);
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
