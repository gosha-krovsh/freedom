#ifndef GAMEOBJECT_ITEM_H_
#define GAMEOBJECT_ITEM_H_

#include <QPixmap>
#include <QString>

#include <string>
#include <utility>
#include <memory>

#include "Model/constants.h"

class Item {
 public:
  enum class Type {
    kApple,
    kBrick,
    kSoap,
    kPrisonerRoba,
    kPoliceRoba,
    kKnife
  };

  Item(Type type, const QString& name, const std::weak_ptr<QPixmap>& image);

  const std::weak_ptr<QPixmap>& GetImage() const;
  QString GetName() const;
  Type GetType() const;

  static QString GetNameByType(Type type);

  bool IsUsable() const;

 private:
  QString name_;
  Type type_;
  std::weak_ptr<QPixmap> image_;
};

#endif  // GAMEOBJECT_ITEM_H_
