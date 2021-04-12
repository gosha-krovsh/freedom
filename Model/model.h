#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <vector>
#include <memory>

#include "GameObject/hero.h"
#include <GameObject/bot.h>

class Model {
 public:
  using GameMap = std::vector<std::vector<std::vector<Object*>>>;

  Model();

  const GameMap& GetMap() const;
  const Hero& GetHero() const;
  const std::vector<std::unique_ptr<Bot>>& GetBots() const;
  Hero& GetHero();

 private:
  std::vector<Object> objects_;
  GameMap map_;
  Hero hero_{Point(1, 6, 1) };
  std::vector<std::unique_ptr<Bot>> bots_;
};

#endif  // MODEL_MODEL_H_
