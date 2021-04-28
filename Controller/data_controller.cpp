#include "data_controller.h"

DataController::DataController(
    const std::shared_ptr<Model>& model) : model_(model) {}

void DataController::Tick(int) {}

// schedule.json structure:
// [
//   [8, 32, [
//     {
//       "action" : "MethodsName",
//       "arguments": ["", "", ""]
//     },
//     ...
//   ]],
//   ...
// ]
std::unique_ptr<Schedule> DataController::ParseSchedule() {
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

  return std::make_unique<Schedule>(schedule);
}

// game_map.json structure:
// {
//   "rooms": [
//     [name, down_left_x, down_left_y, up_right_x, up_right_y],
//     ...
//   ],
//   "map_array" : [
//     [ // z=0
//       [0, 0, ... 0],  // x=0
//       .............
//       [0, 0, ... 0]  // x=n
//     ],
//     ......................
//     [ // z=m
//       [0, 0, ... 0],  // x=0
//       .............
//       [0, 0, ... 0]  // x=n
//     ]
//   ]
// }
std::unique_ptr<GameMap> DataController::ParseGameMap() {
  QFile file(":game_map.json");
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  QJsonObject json_game_map = QJsonDocument::fromJson(file.readAll()).object();

  // Parsing rooms
  std::vector<GameMap::Room> rooms;
  QJsonArray json_rooms = json_game_map["rooms"].toArray();
  if (json_rooms.empty()) {
    qDebug() << "There must be at least 1 room";
  }
  for (const auto& json_room : json_rooms) {
    QJsonArray room_params = json_room.toArray();
    if (room_params.size() != 5) {
      qDebug() << "Invalid number of room constructor parameters";
    }
    rooms.emplace_back(room_params[0].toString(),
                       room_params[1].toInt(), room_params[2].toInt(),
                       room_params[3].toInt(), room_params[4].toInt());
  }

  // Parsing objects
  std::vector<Object*> objects;
  QJsonArray map = json_game_map["map_array"].toArray();
  int z_size = map.size();
  int x_size = map.at(0).toArray().size();
  int y_size = map.at(0).toArray().at(0).toArray().size();
  if (z_size * x_size * y_size <= 0) {
    qDebug() << "Invalid size of the map";
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
        GameMapObjectType object_type =
            static_cast<GameMapObjectType>(line[y].toInt());

        switch (object_type) {
          case GameMapObjectType::kNone: {
            break;
          }
          case GameMapObjectType::kFloor: {
            objects.emplace_back(new Object(Point(x, y, z),
                                            model_->GetImage("floor")));
            break;
          }
          case GameMapObjectType::kWall: {
            objects.emplace_back(new Object(Point(x, y, z),
                                            model_->GetImage("brick")));
            break;
          }
          default: {
            qDebug() << "Not handled type of object";
            break;
          }
        }
      }
    }
  }

  return std::make_unique<GameMap>(x_size, y_size, z_size, objects, rooms);
}
