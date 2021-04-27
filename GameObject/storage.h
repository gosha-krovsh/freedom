#ifndef GAMEOBJECT_STORAGE_H_
#define GAMEOBJECT_STORAGE_H_

#include <vector>

#include "item.h"
#include "Model/constants.h"

class Storage {
 public:
  void PutItem(const Item& item);
  void PutItems(const std::vector<Item>& items);
  Item RemoveItem(int index);

  bool IsValidIndex(int index);
  std::vector<Item> GetItems();

 protected:
  std::vector<Item> items_;
};

#endif  // GAMEOBJECT_STORAGE_H_
