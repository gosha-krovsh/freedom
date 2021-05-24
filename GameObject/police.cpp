#include "police.h"

Police::Police(const QString& name, const Point& coords, int hp)
  : Bot(name, coords, hp, Bot::Type::kPolice) {}

void Police::Tick(int current_tick) {
  Bot::Tick(current_tick);
}
