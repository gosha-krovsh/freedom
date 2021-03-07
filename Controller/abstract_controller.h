#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include <vector>

#include "../GameObject/hero.h"

class AbstractController {
 public:
  virtual ~AbstractController() = default;

  using Map = std::vector<std::vector<std::vector<Object*>>>;
  virtual const Map& GetMap() const = 0;
  virtual const Hero& GetHero() const = 0;
  virtual Hero& GetHero() = 0;

  virtual void UpKeyPressed() = 0;
  virtual void RightKeyPressed() = 0;
  virtual void DownKeyPressed() = 0;
  virtual void LeftKeyPressed() = 0;

  virtual void UpKeyRelease() = 0;
  virtual void RightKeyRelease() = 0;
  virtual void DownKeyRelease() = 0;
  virtual void LeftKeyRelease() = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
