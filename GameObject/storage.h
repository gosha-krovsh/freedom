#ifndef GAMEOBJECT_STORAGE_H_
#define GAMEOBJECT_STORAGE_H_

#include <QDebug>
#include <QString>
#include <vector>

#include "item.h"
#include "Model/constants.h"

class Storage {
 public:
  Storage() = default;
  explicit Storage(const std::vector<Item>& items);

  void PutItem(const Item& item);
  void PutItems(const std::vector<Item>& items);
  Item RemoveItem(int index);

  bool IsValidIndex(int index) const;
  bool HasLessItems(int amount);
  std::vector<Item> GetItems() const;

 protected:
  std::vector<Item> items_;
};

#endif  // GAMEOBJECT_STORAGE_H_
