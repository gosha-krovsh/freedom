#include "item_controller.h"

ItemController::ItemController(const std::shared_ptr<Model>& model) :
    model_(model) {}

void ItemController::UseItem(const Item& item) {
  switch (item.GetType()) {
    // Temp code
    case Item::Type::kApple : {
      Eat(10);
      break;
    }
    case Item::Type::kSoap : {
      model_->GetHero().SetSpeedVector(Point(1, 1));
      break;
    }
    default: {
      qDebug() << "Unhandled usage of item";
      break;
    }
  }
  model_->GetSound().PlayTrack(Sound::kUseItem);
}

void ItemController::Eat(int hp) {
  model_->GetHero().IncreaseHP(hp);
}
