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
        Object::Type object_type = static_cast<Object::Type>(line[y].toInt());

        switch (object_type) {
          case Object::Type::kNone: {
            break;
          }
          case Object::Type::kFloor: {
            objects.emplace_back(new Object(Point(x, y, z),
                                            model_->GetImage("floor")));
            break;
          }
          case Object::Type::kWall: {
            objects.emplace_back(new Wall(Point(x, y, z),
                                          model_->GetImage("brick")));
            break;
          }
          case Object::Type::kChest: {
            // Temporary code
            objects.emplace_back(new Chest(
                Point(x, y, z),
                model_->GetImage("brick"),
                {Item(0, "Block", model_->GetImage("brick"))}));
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

// TODO: delete id in QuestNode ?
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
