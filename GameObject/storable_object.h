#ifndef GAMEOBJECT_STORABLE_H_
#define GAMEOBJECT_STORABLE_H_

#include <vector>

#include "item.h"
#include "Model/constants.h"

class StorableObject {
 public:
  void PutItem(const Item& item);
  void PutItems(const std::vector<Item>& items);
  Item RemoveItem(int index);

  bool IsValidIndex(int index);
  std::vector<Item> GetItems();

 protected:
  std::vector<Item> items_;
};

#endif  // GAMEOBJECT_STORABLE_H_
