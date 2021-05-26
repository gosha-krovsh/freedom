#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <QDebug>

#include <algorithm>
#include <deque>
#include <map>
#include <memory>
#include <set>
#include <unordered_map>
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
  void ExecuteActions(const std::vector<Action>& actions) override;
  void StartQuest(int id) override;

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
  void InteractWithDoor() override;
  void TryToOpenDoor(const Bot& bot);

  Object* FindNearestObjectWithType(Object::Type type) override;
  Object* FindIfNearestObject(
      const std::function<bool(Object*)>& predicate) override;

  std::shared_ptr<Storage> GetInteractableStorage() override;

  void DeleteQuestFromList(const QString& quest_name) override;

  void UpdateQuestList(const QString& quest_name, int index) override;

  void AddQuestToList(const QString& quest_name,
                      const std::vector<QString>& node_strings) override;

  void MoveAllBotsToPoint(const Point& point);

  void CloseMainMenu() override;
  void UpdateSound() override;
  void PlayTrack(Sound::SoundAction action,
                 int volume = constants::kInitVolume);
  void PlayTrackOnce(Sound::SoundAction action,
                     int volume = constants::kInitVolume);

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

  void ProcessPoliceSupervision();
  void ProcessFighting();
  void ProcessFighting(Creature* attacker, Creature* victim);
  void BuildPath(const std::shared_ptr<Bot>& bot, const Point& finish);

  std::vector<Point> CollectPath(const Point& finish,
                                 const std::unordered_map<Point, Point,
                                 Point::HashFunc>& prev) const;

  Object* GetNearestOfTwoObjects(Object* obj1, Object* obj2) const;
  Object* FindNearestStorableObject();

  std::shared_ptr<Bot> FindIfNearestBotInRadius(double radius,
      const std::function<bool(const std::shared_ptr<Bot>&)>& predicate);
  std::shared_ptr<Bot> FindNearestDestroyedBot();
  std::shared_ptr<Bot> FindNearestAliveBotInRadius(double radius);

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
