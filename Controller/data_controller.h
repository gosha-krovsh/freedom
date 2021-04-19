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
#include "GameObject/schedule.h"
#include "Model/model.h"

class DataController {
 public:
  explicit DataController(const std::shared_ptr<Model>& model);

  void Tick(int current_tick);

  static Schedule ParseSchedule();
  static std::unique_ptr<GameMap> ParseGameMap();

 private:
  enum class GameMapObjectType {
    kNone = 0,
    kFloor = 1,
    kWall = 2,
  };

 private:
  std::shared_ptr<Model> model_;
};

#endif  // CONTROLLER_DATA_CONTROLLER_H_