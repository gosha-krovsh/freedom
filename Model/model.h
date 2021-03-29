#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <vector>

#include <GameObject/encrypted_method.h>
#include "GameObject/hero.h"
#include "GameObject/schedule.h"

class Model {
 public:
  using GameMap = std::vector<std::vector<std::vector<Object*>>>;

  explicit Model(const std::map<Time, std::vector<EncryptedMethod>>& actions);

  const GameMap& GetMap() const;
  const Hero& GetHero() const;
  Hero& GetHero();
  const Schedule& GetShedule() const;

  Time& GetTime();

 private:
  std::vector<Object> objects_;
  GameMap map_;
  Schedule schedule_;
  Time time_;
  Hero hero_{Point(1, 6, 1) };
};

#endif  // MODEL_MODEL_H_
