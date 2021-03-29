#ifndef DATA_CONTROLLER_H_
#define DATA_CONTROLLER_H_

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <map>
#include <vector>
#include <memory>

#include "GameObject/encrypted_method.h"
#include "GameObject/game_time.h"

#include "Model/model.h"

class DataController {
 public:
  explicit DataController(std::shared_ptr<Model> model);

  static std::map<Time, std::vector<EncryptedMethod>> ParseShedule();

  void Tick(int current_tick);

 private:
  static int GetMethodId (std::string name);
  static bool Equals (const std::string& lhs, const std::string& rhs);

  std::shared_ptr<Model> model_;
};

#endif  // DATA_CONTROLLER_H_
