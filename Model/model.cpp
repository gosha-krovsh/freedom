#include "model.h"

Model::Model() {};

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

void Model::SetCreatureStorage(std::map<QString,
                                        std::shared_ptr<Storage>>&& items) {
  for (auto name_storage : items) {
    if (name_storage.first == "hero") {
      hero_.SetStorage(std::move(name_storage.second));
    } else {
      auto it = std::find_if(bots_.begin(), bots_.end(),
                             [name_storage] (const Bot& bot) {
        return bot.GetName() == name_storage.first;
      });

      if (it != bots_.end()) {
        it->SetStorage(std::move(name_storage.second));
      }
    }
  }
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

Bot& Model::GetBotByName(const QString& name) {
  return const_cast<Bot&>(const_cast<const Model&>(*this).GetBotByName(name));
}

// NO: Now only bots with name "Hero" are available
const Bot& Model::GetBotByName(const QString& name) const {
  auto it = std::find_if(bots_.begin(), bots_.end(),
                         [name](const Bot& bot) {
                           return (bot.GetName() == name);
                         });
  if (it == bots_.end()) {
    qDebug() << "Invalid bot name";
  }
  return *it;
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
  return image_manager_.GetImage(name);
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

const Quest& Model::GetCurrentQuestById(int id) const {
  auto it = std::find_if(current_quests_.begin(), current_quests_.end(),
                         [id](const Quest& quest) {
                           return (quest.GetId() == id);
                         });
  if (it == current_quests_.end()) {
    qDebug() << "Invalid quest id";
  }
  return *it;
}

void Model::EraseCurrentQuest(int id) {
  auto it = std::find_if(current_quests_.begin(), current_quests_.end(),
                         [id](const Quest& quest) {
                           return (quest.GetId() == id);
                         });
  if (it == current_quests_.end()) {
    qDebug() << "Invalid quest id";
    return;
  }
  current_quests_.erase(it);
}

void Model::AddCurrentQuest(int id) {
  current_quests_.emplace_back(GetQuestById(id));
}

std::shared_ptr<Conversation> Model::GetConversationById(int id) {
  return conversations_.at(id);
}

Sound& Model::GetSound() {
  return sound_;
}

const Sound& Model::GetSound() const {
  return sound_;
}

void Model::SetBots(std::vector<Bot>&& bots) {
  bots_ = std::move(bots);
}
