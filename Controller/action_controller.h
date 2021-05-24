#ifndef CONTROLLER_ACTION_CONTROLLER_H_
#define CONTROLLER_ACTION_CONTROLLER_H_

#include <QDebug>

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "abstract_controller.h"
#include "Model/model.h"
#include "GameObject/point.h"

class ActionController {
 public:
  ActionController(AbstractController* controller,
                   const std::shared_ptr<Model>& model);
  void Call(const Action& method);
  void Call(const std::vector<Action>& methods);
  void Tick(int current_tick);

  // Methods for actions
 private:
  void Move(int id, const Point& place);
  void StartQuest(int id);
  void StartFight(QString name1, QString name2);
  void SetBotConversation(const QString& bot_name, int conversation_id);
  void AddItemToStorage(const Point& coords, Item::Type item_type);
  void AddItemToBot(const QString& bot_name, Item::Type item_type);

 private:
  AbstractController* controller_;
  std::shared_ptr<Model> model_;
};

#endif  // CONTROLLER_ACTION_CONTROLLER_H_
