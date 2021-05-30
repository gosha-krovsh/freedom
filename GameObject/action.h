#ifndef GAMEOBJECT_ACTION_H_
#define GAMEOBJECT_ACTION_H_

#include <QString>
#include <QDebug>

#include <utility>
#include <vector>

class Action {
 public:
  enum ActionType {
    kWrongArg,
    kMove,
    kAddItemToStorage,
    kAddItemToBot,
    kStartQuest,
    kFinishQuest,
    kOpenEyes,
    kCloseEyes,
    kStartConversation,
    kSetBotConversation,
    kStartFight,
    kLockDoor,
    kUnlockDoor,
    kSetTarget,
    kReplayIfNotFinished,
  };

  Action(const QString& name, const std::vector<QString>& parameters);

  ActionType GetActionType() const;
  std::vector<QString> GetParameters() const;

 private:
  ActionType ChooseActionType(const QString& name);

  ActionType action_type_;
  std::vector<QString> parameters_;
};

#endif  // GAMEOBJECT_ACTION_H_
