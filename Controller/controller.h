#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <memory>
#include <vector>

#include "abstract_controller.h"

#include "View/view.h"
#include "Model/model.h"

class Controller : public AbstractController {
 public:
  Controller();
  ~Controller() override = default;

  void Tick() override;

  void SetControlUpKeyState(bool state) override;
  void SetControlRightKeyState(bool state) override;
  void SetControlDownKeyState(bool state) override;
  void SetControlLeftKeyState(bool state) override;

 private:
  struct ControlKeyStates {
    bool up{false};
    bool right{false};
    bool down{false};
    bool left{false};
  };

  void UpdateMovingDirection();

  std::shared_ptr<Model> model_;
  std::unique_ptr<View> view_;

  ControlKeyStates control_key_states_;
};

#endif  // CONTROLLER_CONTROLLER_H_
