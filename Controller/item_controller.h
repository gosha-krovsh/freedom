#ifndef CONTROLLER_ITEM_CONTROLLER_H_
#define CONTROLLER_ITEM_CONTROLLER_H_

#include <QDebug>

#include <memory>

#include "GameObject/item.h"
#include "Model/model.h"

class ItemController {
 public:
  explicit ItemController(const std::shared_ptr<Model>& model);

  void UseItem(Item::Type type);

 private:
  void Eat(int hp);

  std::shared_ptr<Model> model_;
};

#endif  // CONTROLLER_ITEM_CONTROLLER_H_
