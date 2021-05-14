#ifndef CONTROLLER_DATA_CONTROLLER_H_
#define CONTROLLER_DATA_CONTROLLER_H_

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Conversations/conversation.h"
#include "GameObject/action.h"
#include "GameObject/game_time.h"
#include "GameObject/schedule.h"
#include "Model/model.h"

class DataController {
 public:
  explicit DataController(const std::shared_ptr<Model>& model);

  void Tick(int current_tick);

  std::unique_ptr<Schedule> ParseSchedule();
  std::unique_ptr<GameMap> ParseGameMap();
  std::vector<std::shared_ptr<Conversation>> ParseConversations();
  std::vector<Quest> ParseQuests();

 private:
  Action ParseAction(const QString& j_str);
  QuestNode ParseQuestNode(const QJsonArray& j_arr);

  std::shared_ptr<Model> model_;
};

#endif  // CONTROLLER_DATA_CONTROLLER_H_
