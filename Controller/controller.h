#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <QDebug>

#include <memory>
#include <utility>
#include <vector>

#include "abstract_controller.h"
#include "action_controller.h"
#include "data_controller.h"
#include "item_controller.h"
#include "quest_controller.h"

#include "View/view.h"
#include "Model/model.h"

class Controller : public AbstractController {
 public:
  Controller();
  ~Controller() override = default;

  void Tick() override;

  void ExecuteAction(const Action& action) override;

  void HeroAttack() override;
  std::shared_ptr<Conversation> StartConversation() override;
  void FinishConversation() override;

  void SetControlUpKeyState(bool state) override;
  void SetControlRightKeyState(bool state) override;
  void SetControlDownKeyState(bool state) override;
  void SetControlLeftKeyState(bool state) override;
  void UpdateHeroMovingDirection();

  void OnItemPress(int id, int index) override;
  void UseItem(const Item& item) override;
  Object* FindNearestObjectWithType(Object::Type type) override;
  Object* FindIfNearestObject(
      const std::function<bool(Object*)>& predicate) override;

 private:
  struct ControlKeyStates {
    bool up{false};
    bool right{false};
    bool down{false};
    bool left{false};
  };

 private:
  void CheckHeroCollision();
  // Moves item from one object to another via index.
  void MoveItem(int item_index,
                const std::shared_ptr<Storage>& destination,
                const std::shared_ptr<Storage>& source) override;
  void ProcessFighting();
  void ProcessFighting(Creature* attacker, Creature* victim, int* i);
  Bot* FindNearestBotInRadius(double radius);

 private:
  std::shared_ptr<Model> model_;
  std::unique_ptr<View> view_;

  std::unique_ptr<ActionController> actions_controller_;
  std::unique_ptr<DataController> data_controller_;
  std::unique_ptr<QuestController> quest_controller_;
  std::unique_ptr<ItemController> item_controller_;

  ControlKeyStates control_key_states_;
  int current_tick_;
};

#endif  // CONTROLLER_CONTROLLER_H_
