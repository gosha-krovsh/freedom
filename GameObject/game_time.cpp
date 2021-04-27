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
  return std::string(std::to_string(hours_) + ":" + std::to_string(minutes_));
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


