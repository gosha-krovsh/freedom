#include "model.h"

void Model::SetMap(std::unique_ptr<GameMap>&& game_map) {
  map_ = std::move(game_map);
}

void Model::SetSchedule(std::unique_ptr<Schedule>&& schedule) {
  schedule_ = std::move(schedule);
}

void Model::SetConversations(
    std::vector<std::shared_ptr<Conversation>>&& conversations) {
  conversations_ = std::move(conversations);
  hero_.SetCurrentConversation(conversations_[14]);
  GetBotByName("Starec")->SetCurrentConversation(conversations_[0]);
  GetBotByName("Igor")->SetCurrentConversation(conversations_[7]);
  GetBotByName("Rob")->SetCurrentConversation(conversations_[8]);
}

void Model::SetQuests(std::vector<Quest>&& quests) {
  quests_ = std::move(quests);
}

void Model::SetCreatureStorage(std::map<QString,
                                        std::shared_ptr<Storage>>&& items) {
  for (auto name_storage : items) {
    if (name_storage.first == "Hero") {
      hero_.SetStorage(std::move(name_storage.second));
    } else {
      auto it = std::find_if(bots_.begin(), bots_.end(),
                             [name_storage] (const std::shared_ptr<Bot>& bot) {
        return bot->GetName() == name_storage.first;
      });

      if (it != bots_.end()) {
        (*it)->SetStorage(std::move(name_storage.second));
      }
    }
  }
}

void Model::CreateFightingPairIfNotExists(Creature* first, Creature* second) {
  for (const auto& pair : fighting_pairs_) {
    if ((pair.first == first && pair.second == second) ||
        (pair.first == second && pair.second == first)) {
      return;
    }
  }
  first->StartFighting();
  second->StartFighting();
  fighting_pairs_.emplace_back(first, second);
}

void Model::DeleteFinishedFightingPairs() {
  for (int i = 0; i < fighting_pairs_.size(); ++i) {
    if (fighting_pairs_[i].first->IsDestroyed() ||
        fighting_pairs_[i].second->IsDestroyed()) {
      fighting_pairs_[i].first->StopFighting();
      fighting_pairs_[i].second->StopFighting();
      fighting_pairs_.erase(fighting_pairs_.begin() + i);
      --i;
    }
  }
}

const std::vector<std::pair<Creature*, Creature*>>&
    Model::GetFightingPairs() const {
  return fighting_pairs_;
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

std::vector<std::shared_ptr<Bot>>& Model::GetBots() {
  return bots_;
}

const std::vector<std::shared_ptr<Bot>>& Model::GetBots() const {
  return bots_;
}

std::shared_ptr<Bot>& Model::GetBotByName(const QString& name) {
  return const_cast<std::shared_ptr<Bot>&>(
      const_cast<const Model&>(*this).GetBotByName(name));
}

// NO: Now only bots with name "Hero" are available
const std::shared_ptr<Bot>& Model::GetBotByName(const QString& name) const {
  auto it = std::find_if(bots_.begin(), bots_.end(),
                         [name](const std::shared_ptr<Bot>& bot) {
                           return (bot->GetName() == name);
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

void Model::SetBots(std::vector<std::shared_ptr<Bot>>&& bots) {
  bots_ = std::move(bots);
}
