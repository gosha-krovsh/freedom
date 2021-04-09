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

      Action action{name, std::move(parametres)};
      actions.push_back(action);
    }

    schedule[Time(time_array.at(0).toInt(0),
                  time_array.at(1).toInt(0))] = actions;
  }

  return Schedule(schedule);
}

void DataController::Tick(int) {}
