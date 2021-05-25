#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include <memory>
#include <vector>

#include "GameObject/hero.h"
#include "GameObject/bot.h"
#include "GameObject/storage.h"
#include "Conversations/conversation.h"

class AbstractController {
 public:
  virtual ~AbstractController() = default;

  virtual void Tick() = 0;

  virtual void ExecuteAction(const Action& action) = 0;
  virtual void ExecuteActions(const std::vector<Action>& actions) = 0;
  virtual void StartQuest(int id) = 0;

  virtual void HeroAttack() = 0;
  virtual std::shared_ptr<Conversation> StartConversation() = 0;
  virtual void FinishConversation() = 0;

  virtual void SetControlUpKeyState(bool state) = 0;
  virtual void SetControlRightKeyState(bool state) = 0;
  virtual void SetControlDownKeyState(bool state) = 0;
  virtual void SetControlLeftKeyState(bool state) = 0;

  virtual void OnItemPress(int id, int index) = 0;
  virtual void UseItem(const Item& item) = 0;
  virtual void InteractWithDoor() = 0;

  virtual Object* FindNearestObjectWithType(Object::Type type) = 0;
  virtual Object* FindIfNearestObject(
      const std::function<bool(Object*)>& predicate) = 0;
  virtual std::shared_ptr<Storage> GetInteractableStorage() = 0;

  virtual void UpdateQuestList(const QString& quest_name, int index) = 0;
  virtual void AddQuestToList(const QString& quest_name,
                              const std::vector<QString>& node_strings) = 0;
  virtual void DeleteQuestFromList(const QString& quest_name) = 0;

  virtual void CloseMainMenu() = 0;
  virtual void UpdateVolume() = 0;

 private:
  virtual void MoveItem(int index,
                        const std::shared_ptr<Storage>& source,
                        const std::shared_ptr<Storage>& destination) = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
