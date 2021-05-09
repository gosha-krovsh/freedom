#ifndef GAMEOBJECT_ITEM_H_
#define GAMEOBJECT_ITEM_H_

#include <QPixmap>
#include <QString>

#include <string>
#include <utility>
#include <memory>

class Item {
 public:
  Item(int id, const QString& name, const std::weak_ptr<QPixmap>& image);

  const std::weak_ptr<QPixmap>& GetImage() const;
  int GetId() const;
  QString GetName() const;

 private:
  QString name_;
  int id_;
  std::weak_ptr<QPixmap> image_;
};

#endif  // GAMEOBJECT_ITEM_H_
