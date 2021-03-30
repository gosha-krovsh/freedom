#include "data_controller.h"

DataController::DataController(std::shared_ptr<Model> model) {
  model_ = std::move(model);
}

// Parses schedule.json
// schedule.json structure:
/* {
 * "HH::MM" [
 *  {
 *    "action" : "MethodsName",
 *    "arguments": ["", "", ""]
 *  },
 *  ...
 * ],
 * ...
 * }
 * */
std::map<Time, std::vector<Action>> DataController::ParseSchedule() {
  QFile file(":schedule.json");
  file.open(QIODevice::ReadOnly | QIODevice::Text);

  QJsonDocument document = QJsonDocument::fromJson(QByteArray(file.readAll()));
  QJsonObject jschedule_obj = document.object();

  std::map<Time, std::vector<Action>> schedule;

  for (const auto& time_obj : jschedule_obj.keys()) {
    QJsonArray methods_array = jschedule_obj.value(time_obj).toArray();

    std::vector<Action> actions;
    for (const auto& element : methods_array) {
      QJsonObject jparametres = element.toObject();

      std::string name = jparametres.value("action").toString().toStdString();
      std::vector<std::string> parametres;

      for (const auto& param : jparametres.value("arguments").toArray()) {
        std::string str = param.toString().toStdString();
        parametres.push_back(str);
      }

      Action action{std::move(name), std::move(parametres)};
      actions.push_back(action);
    }

    schedule[Time(time_obj.toStdString())] = actions;
  }

  return schedule;
}

void DataController::Tick(int) {}
