#include "item_controller.h"

ItemController::ItemController(const std::shared_ptr<Model>& model) :
    model_(model) {}

void ItemController::UseItem(const Item& item) {
  switch (item.GetType()) {
    // Temp code
    case Item::kApple : {
      Eat(10);
      qDebug() << "Added 10 hp";
      break;
    }
    case Item::kBrick : {
      Eat(100);
      qDebug() << "Added 100 hp";
      break;
    }
  }
}

void ItemController::Eat(int hp) {
  model_->GetHero().IncreaseHP(hp);
}
