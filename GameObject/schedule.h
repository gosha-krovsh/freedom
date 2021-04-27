#ifndef GAMEOBJECT_SCHEDULE_H_
#define GAMEOBJECT_SCHEDULE_H_

#include <map>
#include <utility>
#include <vector>
#include "action.h"
#include "game_time.h"

class Schedule {
 public:
  explicit Schedule(const std::map<Time, std::vector<Action>>&);

  void SetSchedule(const std::map<Time,
                                  std::vector<Action>>& schedule_commands);

  std::vector<Action> GetActionByTime(const Time& time) const;
  bool IsNextActionAvailable(const Time& time) const;

 private:
  std::map<Time, std::vector<Action>> schedule_commands_;
};

#endif  // GAMEOBJECT_SCHEDULE_H_
