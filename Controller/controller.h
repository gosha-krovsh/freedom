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

  const Map& GetMap() const override;
  const Hero& GetHero() const override;
  Hero& GetHero() override;

  void UpKeyPressed() override;
  void RightKeyPressed() override;
  void DownKeyPressed() override;
  void LeftKeyPressed() override;

  void UpKeyRelease() override;
  void RightKeyRelease() override;
  void DownKeyRelease() override;
  void LeftKeyRelease() override;

 private:
  std::unique_ptr<View> view_;
  std::unique_ptr<Model> model_;

  struct ButtonPressStates {
    bool up{ false };
    bool right{ false };
    bool down{ false };
    bool left{ false };
  };
  ButtonPressStates button_states_;

  void ProcessPressedButtons();
};

#endif  // CONTROLLER_CONTROLLER_H_
