#ifndef SCHEDULE_H_
#define SCHEDULE_H_

#include <map>
#include <vector>
#include "encrypted_method.h"
#include "game_time.h"

class Schedule {
 public:
  explicit Schedule(
      const std::map<Time, std::vector<EncryptedMethod>>& calendar);

  void SetShedule(const std::map<Time,
                  std::vector<EncryptedMethod>>& shedule_commands);

  std::vector<EncryptedMethod> GetNextAction(const Time& time) const;
  bool IsNextActionAvailable(const Time& time) const;
 private:
  std::map<Time, std::vector<EncryptedMethod>> shedule_commands_;
};

#endif  // SCHEDULE_H_
