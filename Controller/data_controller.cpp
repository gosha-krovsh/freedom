#include "data_controller.h"

DataController::DataController(const std::shared_ptr<Model>& model) :
                               model_(model) {}

void DataController::Tick(int) {}

// schedule.json structure:
// [
//   [8, 32, [
//     "MyAction1(p1,p2,...)",
//     "MyAction2(p1,p2,...)",
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

    schedule[Time(time_array.at(0).toInt(0),
                  time_array.at(1).toInt(0))] = ParseActions(methods_array);
  }

  return std::make_unique<Schedule>(schedule);
}

#define Case(object_type, point, image_name) \
case Object::Type::object_type: { \
  objects.emplace_back(new Object(point, \
                                  model_->GetImage(image_name), \
                                  Object::Type::object_type)); \
  break; \
} \

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
    if (room_params.size() != 6) {
      qDebug() << "Invalid number of room constructor parameters";
    }
    rooms.emplace_back(room_params[0].toString(),
                       room_params[1] == 1,
                       room_params[2].toInt(), room_params[3].toInt(),
                       room_params[4].toInt(), room_params[5].toInt());
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

  std::map<QString, std::shared_ptr<Storage>> chests_storage =
      ParseMapStorage();
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
        Object::Type object_type = static_cast<Object::Type>(line[y].toInt());

        switch (object_type) {
          case Object::Type::kNone: {
            break;
          }
          case Object::Type::kWall: {
            objects.emplace_back(new Wall(Point(x, y, z),
                                          model_->GetImage("brick")));
            break;
          }
          case Object::Type::kChest:
          case Object::Type::kWardrobe_45:
          case Object::Type::kWardrobe_225:
          case Object::Type::kWardrobe_315: {
            Point point{x, y, z};
            auto storage_it = chests_storage.find(point.ToString());
            std::shared_ptr<Storage> storage = std::make_shared<Storage>();
            if (storage_it != chests_storage.end()) {
              storage = storage_it->second;
            }

            objects.emplace_back(new Chest(
                point,
                model_->GetImage("brick"), storage));
            std::weak_ptr<QPixmap> image;
            if (object_type == Object::Type::kChest) {
              image = model_->GetImage("chest");
            } else if (object_type == Object::Type::kWardrobe_45) {
              image = model_->GetImage("wardrobe_45");
            } else if (object_type == Object::Type::kWardrobe_225) {
              image = model_->GetImage("wardrobe_225");
            } else if (object_type == Object::Type::kWardrobe_315) {
              image = model_->GetImage("wardrobe_315");
            }

            objects.emplace_back(new Chest(point, image, storage));
            break;
          }
          Case(kFloor, Point(x, y, z), "floor")
          Case(kBasketRing225, Point(x, y, z), "basket_ring_225")
          Case(kBasketRing315, Point(x, y, z), "basket_ring_315")
          Case(kFence225, Point(x, y, z), "fence_225")
          Case(kFence315, Point(x, y, z), "fence_315")
          Case(kGrass, Point(x, y, z), "grass")
          Case(kBasketballFloorWithLine45, Point(x, y, z),
               "basketball_floor_with_line_45")
          Case(kBasketballFloorWithLine135, Point(x, y, z),
               "basketball_floor_with_line_135")
          Case(kBasketballFloorWithLine225, Point(x, y, z),
               "basketball_floor_with_line_225")
          Case(kBasketballFloorWithLine315, Point(x, y, z),
               "basketball_floor_with_line_315")
          Case(kBasketballFloor, Point(x, y, z), "basketball_floor")
          Case(kTable, Point(x, y, z), "table")
          Case(kChair, Point(x, y, z), "chair")
          Case(kStoneRoad, Point(x, y, z), "stone_road")
          Case(kMud, Point(x, y, z), "mud")
          Case(kBall, Point(x, y, z), "ball")
          Case(kBed_45, Point(x, y, z), "bed_45")
          Case(kBed_135, Point(x, y, z), "bed_135")
          Case(kBed_225, Point(x, y, z), "bed_225")
          Case(kBed_315, Point(x, y, z), "bed_315")
          Case(kGrating_225, Point(x, y, z), "grating_225")
          Case(kGrating_315, Point(x, y, z), "grating_315")
          case Object::Type::kDoor_225: {
            objects.emplace_back(new Door(Point(x, y, z),
                                          model_->GetImage("door_225"),
                                          Object::Type::kDoor_225));
            break;
          }
          case Object::Type::kDoor_315: {
            objects.emplace_back(new Door(Point(x, y, z),
                                          model_->GetImage("door_315"),
                                          Object::Type::kDoor_315));
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

#undef Case

// conversations.json structure:
// [
//   [  // Conversation.id = 0
//     [0, "Question/text 1", [
//       ["Answer1", id1],
//       ["Answer2", id2, "MyAction(p1,p2,...)"],
//       ["Answer3", id3],
//       ...
//     ]],
//     [id1, "Question/text 2", [
//       ["Answer1", id4],
//       ...
//     ]],
//     ...
//   ],
//   [  // Conversation.id = 1
//     ...
//   ]
//   ...
// ]
std::vector<std::shared_ptr<Conversation>>
DataController::ParseConversations() {
  QFile file(":conversations.json");
  file.open(QIODevice::ReadOnly | QIODevice::Text);

  QJsonArray j_conversations = QJsonDocument::fromJson(file.readAll()).array();
  std::vector<std::shared_ptr<Conversation>> conversations;
  conversations.reserve(j_conversations.size());

  for (int i = 0; i < j_conversations.size(); ++i) {
    QJsonArray j_nodes = j_conversations[i].toArray();
    std::vector<Conversation::Node> nodes;
    nodes.reserve(j_nodes.size());

    for (const auto& j_node_obj : j_nodes) {
      QJsonArray j_node = j_node_obj.toArray();
      if (j_node.size() != 3) {
        qDebug() << "Invalid node: conversation_id = " << i;
      }

      Conversation::Node node;
      node.id = j_node[0].toInt();
      node.text = j_node[1].toString();

      QJsonArray j_answers = j_node[2].toArray();
      for (const auto& j_ans_obj : j_answers) {
        QJsonArray j_ans = j_ans_obj.toArray();
        if (j_ans.size() != 2 && j_ans.size() != 3) {
          qDebug() << "Invalid node: conversation_id = " << i;
        }

        Conversation::Answer answer;
        answer.text = j_ans[0].toString();
        answer.next_node_id = j_ans[1].toInt();
        if (j_ans.size() == 3) {
          answer.action = std::make_shared<Action>(
              ParseAction(j_ans[2].toString()));
        }
        node.answers.emplace_back(std::move(answer));
      }

      nodes.emplace_back(node);
    }
    conversations.emplace_back(std::make_shared<Conversation>(i, nodes));
  }

  return conversations;
}

// quests.json structure:
// [
//   {
//      "Id": 0,
//      "Name": "MyQuestName",
//      "OnStart": [
//        "MyAction(p1,p2...)"
//      ],
//      "Nodes": [
//        [0, "MyQuestNodeName", "MyQuestNodeType(p1,p2...)"]
//      ],
//      "OnFinish": [
//        "MyAction(p1,p2...)"
//      ]
//   }
// ]
std::vector<Quest> DataController::ParseQuests() {
  QFile file(":quests.json");
  file.open(QIODevice::ReadOnly | QIODevice::Text);

  QJsonArray j_quests = QJsonDocument::fromJson(file.readAll()).array();
  std::vector<Quest> quests;
  quests.reserve(j_quests.size());
  for (const auto& j_quest : j_quests) {
    QJsonObject j_quest_obj = j_quest.toObject();
    quests.emplace_back(j_quest_obj["Id"].toInt(),
                        j_quest_obj["Name"].toString(),
                        ParseQuestNodes(j_quest_obj["Nodes"].toArray()),
                        ParseActions(j_quest_obj["OnStart"].toArray()),
                        ParseActions(j_quest_obj["OnFinish"].toArray()));
  }
  return quests;
}

// "Name(p1,p2...)" --> Action("Name", {"p1", "p2"})
Action DataController::ParseAction(const QString& j_str) {
  QString name = j_str.split("(")[0];
  QStringList list_params = (j_str.split("(")[1]).split(")")[0].split(",");
  std::vector<QString> params(list_params.begin(), list_params.end());
  return Action(name, params);
}

std::vector<std::shared_ptr<Bot>> DataController::ParseBots() {
  QFile file(":bots.json");
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  QJsonArray json_bots = QJsonDocument::fromJson(file.readAll()).array();

  std::vector<std::shared_ptr<Bot>> bots;
  for (int i = 0; i < json_bots.size(); ++i) {
    QJsonObject current_bot_params = json_bots[i].toObject();
    QJsonArray current_bot_coords = current_bot_params["coords"].toArray();
    if (current_bot_coords.size() != 3) {
      qDebug() << "Invalid data about bot number "
               << i + 1 << ' ' << current_bot_params.size() << '\n';
    }
    Point start{current_bot_coords[0].toInt(),
                current_bot_coords[1].toInt(),
                current_bot_coords[2].toInt()};

    auto type = current_bot_params["type"].toString();
    if (type == "Prisoner") {
      bots.push_back(std::make_shared<Bot>(
          current_bot_params["name"].toString(), start));
    } else if (type == "Police") {
      bots.push_back(std::make_shared<Police>(
          current_bot_params["name"].toString(), start));
    }
  }

  return bots;
}
  // From items.json parses "creature-items" key
std::map<QString, std::shared_ptr<Storage>>
    DataController::ParseCreatureStorage() {
  QFile file(":items.json");
  file.open(QIODevice::ReadOnly | QIODevice::Text);

  QJsonDocument document = QJsonDocument::fromJson(file.readAll());
  QJsonObject jobject_items_map = document.object();

  QJsonObject jobject_dictionary =
      jobject_items_map.value(QString("dictionary")).toObject();
  QJsonArray creatures_array =
      jobject_items_map.value(QString("creature-items")).toArray();

  std::map<QString, std::shared_ptr<Storage>> result;
  for (auto point_storage : creatures_array) {
    QString creature_name = point_storage.toArray().at(0).toString();

    QJsonArray items_array = point_storage.toArray().at(1).toArray();
    std::vector<Item> items;
    for (auto item : items_array) {
      QString name = item.toString();
      int id = jobject_dictionary.value(name).toInt();
      items.emplace_back(static_cast<Item::Type>(id),
                         name,
                         model_->GetImage(name.toLower()));
    }
    result[creature_name] = std::make_shared<Storage>(items);
  }
  return result;
}

std::map<QString, std::shared_ptr<Storage>> DataController::ParseMapStorage() {
  QFile file(":items.json");
  file.open(QIODevice::ReadOnly | QIODevice::Text);

  QJsonDocument document = QJsonDocument::fromJson(file.readAll());
  QJsonObject jobject_items_map = document.object();

  QJsonObject jobject_dictionary =
      jobject_items_map.value(QString("dictionary")).toObject();
  QJsonArray points_array =
      jobject_items_map.value(QString("map-items")).toArray();

  std::map<QString, std::shared_ptr<Storage>> result;
  for (auto point_storage : points_array) {
    QJsonArray point_array = point_storage.toArray().at(0).toArray();
    Point point{point_array.at(0).toInt(),
                point_array.at(1).toInt(),
                point_array.at(2).toInt()};

    QJsonArray items_array = point_storage.toArray().at(1).toArray();
    std::vector<Item> items;
    for (auto item : items_array) {
      QString name = item.toString();
      int id = jobject_dictionary.value(name).toInt();
      items.emplace_back(Item(static_cast<Item::Type>(id),
                              name,
                              model_->GetImage(name.toLower())));
    }
    result[point.ToString()] = std::make_shared<Storage>(items);
  }
  return result;
}

std::vector<Action> DataController::ParseActions(const QJsonArray& j_arr) {
  std::vector<Action> actions;
  actions.reserve(j_arr.size());
  for (const auto& element : j_arr) {
    actions.emplace_back(ParseAction(element.toString()));
  }
  return actions;
}

// Ex: ["MyQuestNodeName", "MoveToDestination(7, 9, 1)"]
QuestNode DataController::ParseQuestNode(const QJsonArray& j_arr) {
  if (j_arr.size() != 2) {
    qDebug() << "Invalid number of QuestNode arguments";
  }

  QString j_type_and_params_str = j_arr[1].toString();
  QString type_str = j_type_and_params_str.split("(")[0];
  QStringList list_params = (j_type_and_params_str.split("(")[1]).
                            split(")")[0].split(",");
  std::vector<QString> params(list_params.begin(), list_params.end());

  return QuestNode(j_arr[0].toString(), type_str, params);
}

std::vector<QuestNode>
    DataController::ParseQuestNodes(const QJsonArray& j_arr) {
  std::vector<QuestNode> quest_nodes;
  quest_nodes.reserve(j_arr.size());
  for (const auto& j_quest_node : j_arr) {
    quest_nodes.emplace_back(ParseQuestNode(j_quest_node.toArray()));
  }
  return quest_nodes;
}
