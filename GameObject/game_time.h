#ifndef GAMEOBJECT_GAME_TIME_H_
#define GAMEOBJECT_GAME_TIME_H_

#include <string>

class Time {
 public:
  Time() = default;
  Time(int hours, int minutes);

  Time& operator=(const Time& time) = default;

  void AddMinutes(int minutes);

  int GetMinutes() const;
  int GetHours() const;

  bool operator==(const Time&) const;
  bool operator!=(const Time&) const;
  bool operator<(const Time&) const;
  bool operator<=(const Time&) const;
  bool operator>(const Time&) const;
  bool operator>=(const Time&) const;

  std::string ToString() const;  // Fromat HH:MM

 private:
  int minutes_ = 0;
  int hours_ = 0;
};

#endif  // GAMEOBJECT_GAME_TIME_H_
