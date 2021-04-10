#include "data_controller.h"

DataController::DataController(
    const std::shared_ptr<Model>& model) : model_(model) {}

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

std::unique_ptr<GameMap> DataController::ParseGameMap() {
  QFile file(":game_map.json");
  file.open(QIODevice::ReadOnly | QIODevice::Text);

  QJsonDocument document = QJsonDocument::fromJson(file.readAll());
  std::vector<Object*> objects;

  QJsonArray map = document.array();
  int z_size = map.size();
  int x_size = map.at(0).toArray().size();
  int y_size = map.at(0).toArray().at(0).toArray().size();
  if (z_size * x_size * y_size <= 0) {
    qDebug() << "Invalid size of the map during parsing";
  }
  objects.reserve(z_size * x_size * y_size);

  for (int z = 0; z < z_size; ++z) {
    QJsonArray surface = map[z].toArray();
    if (surface.size() != x_size) {
      qDebug() << "Map consists of jagged array: z =" << z;
    }
    for (int x = 0; (x < x_size) && (x < surface.size()); ++x) {
      QJsonArray line = surface[x].toArray();
      if (line.size() != y_size) {
        qDebug() << "Map consists of jagged array: z =" << z << ", x =" << x;
      }
      for (int y = 0; (y < y_size) && (y < line.size()); ++y) {
        int type = line[y].toInt();
        switch (type) {
          case 0: {  // no sense to add nullptr
            break;
          }
          case 1: {  // floor with no image
            objects.emplace_back(new Object{Point(x, y, z), nullptr});
            break;
          }
          case 2: {
            static std::shared_ptr<QPixmap> brick_image =
                std::make_shared<QPixmap>(":brick.png");
            objects.emplace_back(new Object{Point(x, y, z), brick_image});
            break;
          }
          default: {
            qDebug() << "Not handled type of object during parsing";
            break;
          }
        }
      }
    }
  }

  return std::make_unique<GameMap>(x_size, y_size, z_size, objects);
}
