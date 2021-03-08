#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <memory>
#include <vector>

#include "abstract_controller.h"

#include "../View/view.h"
#include "../Model/model.h"

class Controller : public AbstractController {
 public:
  Controller();

  void Tick() override;

  void SetControlUpKeyState(bool state) override;
  void SetControlRightKeyState(bool state) override;
  void SetControlDownKeyState(bool state) override;
  void SetControlLeftKeyState(bool state) override;

 private:
  std::unique_ptr<Model> model_;
  std::unique_ptr<View> view_;

  struct ControlSystemKeyStates {
    bool up{ false };
    bool right{ false };
    bool down{ false };
    bool left{ false };
  };
  ControlSystemKeyStates key_states;

  void ProcessControlKeyStates();
};

#endif  // CONTROLLER_CONTROLLER_H_
