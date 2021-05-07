#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include <memory>
#include <vector>

#include "GameObject/hero.h"

class AbstractController {
 public:
  virtual ~AbstractController() = default;

  virtual void Tick() = 0;

  virtual void HeroAttack() = 0;
  virtual std::shared_ptr<Conversation> StartConversation() = 0;
  virtual void FinishConversation() = 0;

  virtual void SetControlUpKeyState(bool state) = 0;
  virtual void SetControlRightKeyState(bool state) = 0;
  virtual void SetControlDownKeyState(bool state) = 0;
  virtual void SetControlLeftKeyState(bool state) = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
