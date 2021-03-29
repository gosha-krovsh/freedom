#include "schedule.h"

Schedule::Schedule(
    const std::map<Time, std::vector<EncryptedMethod>>& calendar):
    shedule_commands_(calendar) {}

bool Schedule::IsNextActionAvailable(const Time& time) const {
  if (shedule_commands_.find(time) != shedule_commands_.end()) {
    return true;
  }

  return false;
}

std::vector<EncryptedMethod> Schedule::GetNextAction(const Time& time) const {
  return shedule_commands_.at(time);
}

void Schedule::SetShedule(const std::map<Time,
                          std::vector<EncryptedMethod>>& shedule_commands) {
  shedule_commands_ = shedule_commands;
}

