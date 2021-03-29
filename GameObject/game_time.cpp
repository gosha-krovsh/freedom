#include "game_time.h"

Time::Time(const Time& time) {
  minutes_ = time.minutes_;
  hours_ = time.hours_;
}

Time::Time(const std::string& str_time) {
  int position = str_time.find(':');
  if (position != std::string::npos) {
    hours_ = std::stoi(str_time.substr(0, position));
    minutes_ = std::stoi(str_time.substr(position + 1,
                         str_time.end() - str_time.begin() - position - 1));
  }
}

Time::Time(int hours, int minutes) : hours_(hours), minutes_(minutes) {}

void Time::AddMinutes(int minutes) {
  minutes_ += minutes % 60;
  hours_ += minutes / 60;

  if (minutes_ >= 60) {
    hours_ += 1;
  }

  hours_ = hours_ % 24;
}

int Time::GetMinutes() const {
  return minutes_;
}

int Time::GetHours() const {
  return hours_;
}

std::string Time::GetTime() const {
  return ToString();
}

std::string Time::ToString() const {
  return std::string(std::to_string(hours_) + ":" + std::to_string(minutes_));
}

bool Time::operator==(const Time& time) const {
  return hours_ == time.hours_ && minutes_ == time.minutes_;
}

bool Time::operator<(const Time& time) const {
  if (hours_ < time.hours_ ||
      hours_ == time.hours_ && minutes_ < time.minutes_) {
    return true;
  }
  return false;
}


