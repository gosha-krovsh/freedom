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

#include "GameObject/action.h"
#include "GameObject/game_time.h"

#include "Model/model.h"

class DataController {
 public:
  explicit DataController(std::shared_ptr<Model> model);

  static std::map<Time, std::vector<Action>> ParseSchedule();

  void Tick(int current_tick);

 private:
  std::shared_ptr<Model> model_;
};

#endif  // CONTROLLER_DATA_CONTROLLER_H_
