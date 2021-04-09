#include "data_controller.h"


DataController::DataController(const std::shared_ptr<Model>& model) :
    model_(model) {}

/* Parses schedule.json
 * schedule.json structure:
 * [
 * [8, 32, [
 *  {
 *    "action" : "MethodsName",
 *    "arguments": ["", "", ""]
 *  },
 *  ...
 * ]],
 * ...
 * ]
 * */
Schedule DataController::ParseSchedule() {
  QFile file(":schedule.json");
  file.open(QIODevice::ReadOnly | QIODevice::Text);

  QJsonDocument document = QJsonDocument::fromJson(file.readAll());
  QJsonArray jschedule_array = document.array();

  std::map<Time, std::vector<Action>> schedule;

  for (const auto& time : jschedule_array) {
    QJsonArray time_array = time.toArray();
    QJsonArray methods_array = time_array.at(2).toArray();

    std::vector<Action> actions;
    for (const auto& element : methods_array) {
      QJsonObject jparametres = element.toObject();

      std::string name = jparametres.value("action").toString().toStdString();
      std::vector<std::string> parametres;

      for (const auto& param : jparametres.value("arguments").toArray()) {
        std::string str = param.toString().toStdString();
        parametres.push_back(str);
      }

      Action action{name, parametres};
      actions.push_back(action);
    }

    schedule[Time(time_array.at(0).toInt(0),
                  time_array.at(1).toInt(0))] = actions;
  }

  return Schedule(schedule);
}

void DataController::Tick(int) {}

GameMap DataController::ParseGameMap() {
  QFile file(":game_map.json");
  file.open(QIODevice::ReadOnly | QIODevice::Text);

  QJsonDocument document = QJsonDocument::fromJson(file.readAll());
  std::vector<std::vector<std::vector<Object*>>> objects;

  QJsonArray map = document.array();
  objects.reserve(map.size());
  for (int z = 0; z < map.size(); ++z) {
    QJsonArray surface = map[z].toArray();
    objects.emplace_back(std::vector<std::vector<Object*>>{});
    objects.back().reserve(surface.size());
    for (int x = 0; x < surface.size(); ++x) {
      QJsonArray line = surface[x].toArray();
      objects.back().emplace_back(std::vector<Object*>{});
      objects.back().back().reserve(line.size());
      for (int y = 0; y < line.size(); ++y) {
        int type = line[y].toInt();
        switch (type) {
          case 0: {
            objects.back().back().emplace_back(nullptr);
            break;
          }
          case 1: {  // floor with no image
            objects.back().back().emplace_back(new Object{Point(x, y, z),
                                                          nullptr});
            break;
          }
          case 2: {
            static std::shared_ptr<QPixmap> img = std::make_shared<QPixmap>(":brick.png");
            objects.back().back().emplace_back(
                new Object{Point(x, y, z), img});
            break;
          }
          default: {
            qDebug() << "Here";
            break;
          }
        }
      }
    }
  }

  // Print Info (TEMP)
  for (auto& surface : objects) {
    for (auto& line : surface) {
      for (auto& block : line) {
        if (block) {
          block->PrintInfo();
        } else {
          qDebug() << "nullptr\n";
        }
      }
      qDebug() << "\n";
    }
    qDebug() << "-----------\n";
  }

  qDebug() << "\n";
  return GameMap(objects);
}
