#include "data_controller.h"

#include <utility>

DataController::DataController(std::shared_ptr<Model> model) {
  model_ = std::move(model);
}

// Parses shedule.json
// shedule.json structure:
/* {
 * "HH::MM" [
 *  {
 *    "name" : "MethodsName",
 *    "commands": ["", "", ""]
 *  },
 *  ...
 * ],
 * ...
 * }
 * */
std::map<Time, std::vector<EncryptedMethod>> DataController::ParseShedule() {
  QFile file = QFile(":schedule.json");
  file.open(QIODevice::ReadOnly | QIODevice::Text);

  QJsonDocument document = QJsonDocument::fromJson(QByteArray(file.readAll()));
  QJsonObject jshedule_obj = document.object();

  std::map<Time, std::vector<EncryptedMethod>> shedule;

  for (const auto& time_obj : jshedule_obj.keys()) {
    QJsonArray methods_array = jshedule_obj.value(time_obj).toArray();

    std::vector<EncryptedMethod> methods;
    for (const auto& element : methods_array) {
      QJsonObject parametres = element.toObject();
      EncryptedMethod method;

      method.name = parametres.value("name").toString().toStdString();
      method.id = GetMethodId(method.name);

      for (const auto& param : parametres.value("commands").toArray()) {
        std::string str = param.toString().toStdString();
        method.parameters.push_back(str);
      }

      methods.push_back(method);
    }

    shedule[Time(time_obj.toStdString())] = methods;
  }

  return shedule;
}

int DataController::GetMethodId(std::string name) {
  if (Equals(name, "move")) {
    return 1;
  }

  return 0;
}

bool DataController::Equals(const std::string& lhs, const std::string& rhs) {
  return std::equal(lhs.begin(), lhs.end(),
                    rhs.begin(), rhs.end(),
                    [](char a, char b) {
                      return tolower(a) == tolower(b);
                    });
}

void DataController::Tick(int) {}
