#include "hero.h"

Hero::Hero(const Point& coords)
  : Creature(coords, "Hero", constants::kHP) {}

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

Point Hero::GetViewVector() const {
  Point view_vector(-1, 0);
  view_vector.Rotate(-135 + 45 * static_cast<int>(view_direction_));
  return view_vector;
}

void Hero::UpdateSpeedVector(const Point& screen_vector) {
  Point speed_vector = Point::FromScreenPoint(screen_vector);
  speed_vector.Normalize();

  // Making movement more realistic in isometric world: equal displacement in
  // isometric view in all directions, except horizontal (a slow down here)
  if (std::abs(screen_vector.y) < constants::kEps) {
    // horizontal movement
    speed_vector *= constants::kIsometricSpeedCoefficient;
  } else if (std::abs(screen_vector.x) >= constants::kEps &&
      std::abs(screen_vector.y) >= constants::kEps) {
    // diagonal movement
    speed_vector /= std::sqrt(2);
  }

  SetSpeedVector(speed_vector);
}

void Hero::OnDead() {}
