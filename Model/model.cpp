#include "model.h"

Model::Model(const Schedule& schedule,
             std::unique_ptr<GameMap> game_map) :
    time_(Time(8, 30)),
    schedule_(schedule),
    map_(std::move(game_map)) {
  // TODO: parse it from json
  std::vector<std::shared_ptr<AbstractQuestNode>> quest_nodes{
      std::make_shared<MoveToDestinationQuestNode>(0, "MyQuestNodeName",
                                                   Point{3, 3, 1})
  };
  quests_.emplace_back(std::make_shared<Quest>(0, "MyQuestName", quest_nodes));
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

std::shared_ptr<Quest> Model::GetCurrentQuest() const {
  return current_quest;
}

void Model::ResetCurrentQuest() {
  current_quest = nullptr;
}

void Model::SetCurrentQuestById(int id) {
  auto it = std::find_if(quests_.begin(), quests_.end(),
                         [id](const std::shared_ptr<Quest>& quest) {
                           return (quest->GetId() == id);
  });
  if (it == quests_.end()) {
    qDebug() << "Invalid quest id";
  } else {
    current_quest = *it;
  }
}

