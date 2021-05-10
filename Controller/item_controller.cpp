#include "item_controller.h"

ItemController::ItemController(const std::shared_ptr<Model>& model) :
    model_(model) {}

void ItemController::UseItem(Item::Type type) {
  switch (type) {
    // Temp code
    case Item::kApple : {
      Eat(10);
      qDebug() << "Added 10 hp";
    }
    case Item::kBrick : {
      Eat(100);
      qDebug() << "Added 100 hp";
    }
  }
}

void ItemController::Eat(int hp) {
  model_->GetHero().IncreaseHP(hp);
}
