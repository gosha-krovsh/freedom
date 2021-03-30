#include "schedule.h"

Schedule::Schedule(std::map<Time, std::vector<Action>> commands) :
    schedule_commands_(std::move(commands)) {}

bool Schedule::IsNextActionAvailable(const Time& time) const {
  return schedule_commands_.find(time) != schedule_commands_.end();
}

std::vector<Action> Schedule::GetActionByTime(const Time& time) const {
  return schedule_commands_.at(time);
}

void Schedule::SetSchedule(const std::map<Time,
                           std::vector<Action>>& schedule_commands) {
  schedule_commands_ = schedule_commands;
}

