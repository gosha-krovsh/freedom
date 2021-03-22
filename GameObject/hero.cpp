#include "hero.h"

Hero::Hero(const Point& coords, const QPixmap& image)
  : Creature(coords, image, "", constants::kHP) {}

void Hero::Tick(int current_tick) {
  Creature::Tick(current_tick);
}

void Hero::UpdateMovement(bool left, bool up, bool right, bool down) {
  double x = (right ? 1 : 0) - (left ? 1 : 0);
  double y = (up ? 1 : 0) - (down ? 1 : 0);
  Point screen_vector{x, y};
  UpdateSpeedVector(screen_vector);
  UpdateViewDirection();
}

void Hero::UpdateSpeedVector(const Point& screen_vector) {
  speed_vector_ = Point::FromScreenPoint(screen_vector);
  speed_vector_.Normalize();

  // Making movement more realistic in isometric world: equal displacement in
  // isometric view in all directions, except horizontal (a slow down here)
  if (std::abs(screen_vector.y) < constants::kEps) {
    // horizontal movement
    speed_vector_ *= constants::kIsometricSpeedCoefficient;
  } else if (std::abs(screen_vector.x) >= constants::kEps &&
      std::abs(screen_vector.y) >= constants::kEps) {
    // diagonal movement
    speed_vector_ /= std::sqrt(2);
  }
}

void Hero::OnDead() {}
