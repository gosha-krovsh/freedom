#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <vector>
#include <GameObject/game_map.h>

#include "GameObject/hero.h"

class Model {
 public:
  Model();

  const GameMap& GetMap() const;
  const Hero& GetHero() const;
  Hero& GetHero();

 private:
  std::vector<Object> objects_;
  GameMap map_;
  Hero hero_{Point(1, 6, 1)};
};

#endif  // MODEL_MODEL_H_
