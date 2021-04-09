#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <memory>
#include <vector>

#include "GameObject/hero.h"

class Model {
 public:
  using GameMap = std::vector<std::vector<std::vector<Object*>>>;

  Model();

  const GameMap& GetMap() const;
  const Hero& GetHero() const;
  Hero& GetHero();

 private:
  std::vector<Object> objects_;
  GameMap map_;
  Hero hero_{Point(1, 6, 1)};

  std::shared_ptr<QPixmap>
      brick_image = std::make_shared<QPixmap>(":brick.png");
};

#endif  // MODEL_MODEL_H_
