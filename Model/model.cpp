#include "model.h"

Model::Model(const Schedule& schedule,
             std::unique_ptr<GameMap> game_map) :
    time_(Time(8, 30)),
    schedule_(schedule),
    map_(std::move(game_map)) {
  bots_.emplace_back(std::make_unique<Bot>("Hero", Point(4, 1, 1),
                                           std::vector<Point>(
                                               {Point(4, 6, 1),
                                                Point(1, 6, 1),
                                                Point(1, 1, 1),
                                                Point(4, 1, 1),
                                                Point(4, 6, 1),
                                                Point(2, 6, 1),
                                                Point(2, 9, 1),
                                                Point(7, 9, 1)})));

  /// TODO: Parse bots from JSON
  // TODO: parse it from json
  std::vector<QuestNode> quest_nodes{
      QuestNode(0, "MyQuestNodeName", QuestNode::Type::kMoveToDestination,
                std::vector<QString>{"7", "9", "1"})
  };
  quests_.emplace_back(0, "MyQuestName", quest_nodes);
}

Model::~Model() {
  Wall::DeleteImage();
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

const Quest& Model::GetQuestById(int id) const {
  if (id < 0 || id >= quests_.size()) {
    qDebug() << "Invalid quest id";
  }
  return quests_[id];
}

const std::list<Quest>& Model::GetCurrentQuests() const {
  return current_quests_;
}

std::list<Quest>& Model::GetCurrentQuests() {
  return current_quests_;
}
std::vector<std::unique_ptr<Bot>>& Model::GetBots() {
  return bots_;
}
