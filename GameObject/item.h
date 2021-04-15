#ifndef GAMEOBJECT_ITEM_H_
#define GAMEOBJECT_ITEM_H_

#include <QPixmap>

#include <string>
#include <utility>

class Item {
 public:
  Item(std::string name, int id, const QPixmap& image);

  QPixmap& GetImage();
  int GetId() const;
  std::string GetName() const;

 private:
  std::string name_;
  int id_;
  QPixmap image_;
};

#endif  // GAMEOBJECT_ITEM_H_
