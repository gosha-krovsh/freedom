#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "image_manager.h"
#include "GameObject/action.h"
#include "GameObject/game_map.h"
#include "GameObject/hero.h"
#include "GameObject/schedule.h"

class Model {
 public:
  void SetMap(std::unique_ptr<GameMap>&& game_map);
  void SetSchedule(std::unique_ptr<Schedule>&& schedule);

  const GameMap& GetMap() const;
  GameMap& GetMap();
  const Hero& GetHero() const;
  Hero& GetHero();
  const Schedule& GetSchedule() const;
  Time& GetTime();
  const Time& GetTime() const;
  std::weak_ptr<QPixmap> GetImage(const QString& name);

 private:
  std::unique_ptr<GameMap> map_;
  std::unique_ptr<Schedule> schedule_;
  Hero hero_{Point(1, 1, 1)};
  Time time_{Time(8, 30)};
  ImageManager image_manager;
};

#endif  // MODEL_MODEL_H_
