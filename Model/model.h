#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <memory>
#include <vector>

#include "GameObject/hero.h"
#include "GameObject/wall.h"

class Model {
 public:
  using GameMap = std::vector<std::vector<std::vector<Object*>>>;

  Model();
  ~Model();

  const GameMap& GetMap() const;
  std::vector<Object*>& GetObjects();
  const Hero& GetHero() const;
  Hero& GetHero();

 private:
  std::vector<Object*> objects_;
  GameMap map_;
  Hero hero_{Point(1, 6, 1)};
};

#endif  // MODEL_MODEL_H_
