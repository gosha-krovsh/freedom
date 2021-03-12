#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <vector>

#include "../GameObject/hero.h"

class Model {
 public:
  using GameMap = std::vector<std::vector<std::vector<Object*>>>;

  Model();

  const GameMap& GetMap() const;
  const Hero& GetHero() const;
  Hero& GetHero();

 private:
  std::vector<Object> objects_ {
    Object(Coordinates(0, 5, 0), QPixmap(":brick.png")),
    Object(Coordinates(1, 5, 0), QPixmap(":brick.png")),
    Object(Coordinates(2, 5, 0), QPixmap(":brick.png")),
    Object(Coordinates(0, 6, 0), QPixmap(":brick.png")),
    Object(Coordinates(1, 6, 0), QPixmap(":brick.png")),
    Object(Coordinates(2, 6, 0), QPixmap(":brick.png")),
    Object(Coordinates(0, 7, 0), QPixmap(":brick.png")),
    Object(Coordinates(1, 7, 0), QPixmap(":brick.png")),
    Object(Coordinates(2, 7, 0), QPixmap(":brick.png")),
  };

  GameMap map_;

  Hero hero_{Coordinates(1, 6, 1) };
};

#endif  // MODEL_MODEL_H_
