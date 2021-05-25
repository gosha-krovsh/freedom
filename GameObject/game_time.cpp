#include "game_time.h"

Time::Time(int hours, int minutes) : hours_(hours), minutes_(minutes) {}

void Time::AddMinutes(int minutes) {
  hours_ = (hours_ + (minutes + minutes_) / 60) % 24;
  minutes_ = (minutes_ + minutes) % 60;
}

int Time::GetMinutes() const {
  return minutes_;
}

int Time::GetHours() const {
  return hours_;
}

std::string Time::ToString() const {
  std::string hours = std::to_string(hours_);
  std::string minutes = std::to_string(minutes_);
  if (hours_ < 10) {
    hours = std::string("0") + hours;
  }
  if (minutes_ < 10) {
    minutes = std::string("0") + minutes;
  }
  return hours + ":" + minutes;
}

bool Time::operator==(const Time& time) const {
  return (hours_ == time.hours_) && (minutes_ == time.minutes_);
}

bool Time::operator!=(const Time& time) const {
  return !(*this == time);
}

bool Time::operator<(const Time& time) const {
  return hours_ < time.hours_ ||
      (hours_ == time.hours_ && minutes_ < time.minutes_);
}

bool Time::operator>=(const Time& time) const {
  return !(*this < time);
}

bool Time::operator<=(const Time& time) const {
  return (*this < time) || (*this == time);
}
bool Time::operator>(const Time& time) const {
  return !(*this <= time);
}


