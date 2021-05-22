#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <QString>

#include <list>
#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "image_manager.h"
#include "Conversations/conversation.h"
#include "GameObject/action.h"
#include "GameObject/bot.h"
#include "GameObject/game_map.h"
#include "GameObject/hero.h"
#include "GameObject/chest.h"
#include "GameObject/wall.h"
#include "GameObject/schedule.h"
#include "GameObject/sound.h"
#include "Quests/quest.h"

class Model {
 public:
  Model();

  void SetMap(std::unique_ptr<GameMap>&&);
  void SetSchedule(std::unique_ptr<Schedule>&&);
  void SetConversations(std::vector<std::shared_ptr<Conversation>>&&);
  void SetBots(std::vector<Bot>&& bots);
  void SetQuests(std::vector<Quest>&&);
  void SetCreatureStorage(std::map<QString, std::shared_ptr<Storage>>&& items);

  void CreateFightingPair(Creature* first, Creature* second);
  void DeleteFightingPairWithIndex(int index);
  std::pair<Creature*, Creature*> GetFightingPairWithIndex(int index);
  int GetNumberOfFightingPairs() const;

  const GameMap& GetMap() const;
  GameMap& GetMap();

  Sound& GetSound();
  const Sound& GetSound() const;

  const Hero& GetHero() const;
  Hero& GetHero();

  Time& GetTime();
  const Time& GetTime() const;

  const Schedule& GetSchedule() const;
  std::weak_ptr<QPixmap> GetImage(const QString& name);

  const std::vector<Bot>& GetBots() const;
  std::vector<Bot>& GetBots();
  const Bot& GetBotByName(const QString& name) const;
  Bot& GetBotByName(const QString& name);

  const std::vector<Quest>& GetCurrentQuests() const;
  std::vector<Quest>& GetCurrentQuests();
  void AddCurrentQuest(int id);
  const Quest& GetCurrentQuestById(int id) const;
  void EraseCurrentQuest(int id);

  std::shared_ptr<Conversation> GetConversationById(int id);

 private:
  const Quest& GetQuestById(int id) const;

  std::unique_ptr<GameMap> map_;
  std::unique_ptr<Schedule> schedule_;
  Hero hero_{Point(1, 1, 1)};
  Time time_{Time(8, 30)};
  ImageManager image_manager_;
  Sound sound_;
  std::vector<Bot> bots_;
  std::vector<Quest> quests_;
  std::vector<Quest> current_quests_;
  std::vector<std::pair<Creature*, Creature*>> fighting_pairs_;
  std::vector<std::shared_ptr<Conversation>> conversations_;
};

#endif  // MODEL_MODEL_H_
