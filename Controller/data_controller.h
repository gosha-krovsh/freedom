#ifndef CONTROLLER_DATA_CONTROLLER_H_
#define CONTROLLER_DATA_CONTROLLER_H_

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Conversations/conversation.h"
#include "GameObject/action.h"
#include "GameObject/game_time.h"
#include "GameObject/schedule.h"
#include "GameObject/storage.h"
#include "GameObject/door.h"
#include "Model/model.h"

class DataController {
 public:
  explicit DataController(const std::shared_ptr<Model>& model);

  void Tick(int current_tick);

  std::unique_ptr<Schedule> ParseSchedule();
  std::unique_ptr<GameMap> ParseGameMap();
  std::vector<std::shared_ptr<Conversation>> ParseConversations();
  std::map<QString, std::shared_ptr<Storage>> ParseCreatureStorage();

 private:
  // This method used in ParseGameMap to put Storage into Chests
  std::map<QString, std::shared_ptr<Storage>> ParseMapStorage();
  Action ParseAction(const QString& j_str);

  std::shared_ptr<Model> model_;
};

#endif  // CONTROLLER_DATA_CONTROLLER_H_
