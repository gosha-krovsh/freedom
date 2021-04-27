#ifndef GAMEOBJECT_ITEM_H_
#define GAMEOBJECT_ITEM_H_

#include <QPixmap>
#include <QString>

#include <string>
#include <utility>

class Item {
 public:
  Item(int id, const QString& name, const QPixmap& image);

  const QPixmap& GetImage() const;
  int GetId() const;
  QString GetName() const;

 private:
  QString name_;
  int id_;
  QPixmap image_;
};

#endif  // GAMEOBJECT_ITEM_H_
