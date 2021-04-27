#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <QString>

#include <vector>

#include "GameObject/hero.h"
#include "GameObject/chest.h"

class Model {
 public:
  using GameMap = std::vector<std::vector<std::vector<Object*>>>;

  Model();

  const GameMap& GetMap() const;
  const Hero& GetHero() const;
  Hero& GetHero();

 private:
  std::vector<Object*> objects_;
  GameMap map_;
  Hero hero_{Point(1, 6, 1) };
};

#endif  // MODEL_MODEL_H_
