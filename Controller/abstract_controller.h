#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include <memory>
#include <vector>

#include "GameObject/hero.h"
#include "GameObject/storage.h"

class AbstractController {
 public:
  virtual ~AbstractController() = default;

  virtual void Tick() = 0;

  virtual void HeroAttack() = 0;

  virtual void SetControlUpKeyState(bool state) = 0;
  virtual void SetControlRightKeyState(bool state) = 0;
  virtual void SetControlDownKeyState(bool state) = 0;
  virtual void SetControlLeftKeyState(bool state) = 0;

  virtual void OnItemPress(int id, int index) = 0;
  virtual Object* FindNearestObjectWithType(Object::Type type) = 0;

 private:
  virtual void MoveItem(int index,
                        const std::shared_ptr<Storage>& source,
                        const std::shared_ptr<Storage>& destination) = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
