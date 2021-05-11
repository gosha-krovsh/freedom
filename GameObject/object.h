#ifndef GAMEOBJECT_OBJECT_H_
#define GAMEOBJECT_OBJECT_H_

#include <QPainter>

#include <memory>

#include "Model/constants.h"
#include "point.h"
#include "interacting_object.h"
#include "storage.h"

class Object {
 public:
  enum class Type {
    kNone,
    kFloor,
    kWall,
    kChest,
    kBasketRing225 = 4,
    kBasketRing315 = 5,
  };

 public:
  explicit Object(const Point& coords,
                  const std::weak_ptr<QPixmap>& image =
                      std::weak_ptr<QPixmap>(),
                  Type type = Type::kNone);
  virtual ~Object() = default;

  virtual void Tick(int current_time);

  virtual Point GetDrawOffset() const;
  Point GetCoordinates() const;
  double GetX() const;
  double GetY() const;
  double GetZ() const;
  int GetRoundedX() const;
  int GetRoundedY() const;
  int GetRoundedZ() const;
  int GetFlooredX() const;
  int GetFlooredY() const;
  void SetCoordinates(const Point& coords);
  void SetX(double x);
  void SetY(double y);
  void SetZ(double z);

  std::shared_ptr<Storage> GetStorage();

  bool IsTouchable() const;
  bool IsStorable() const;
  bool IsType(Type object_type) const;
  bool ToDelete() const;

  void Draw(QPainter* painter) const;
  virtual void Interact(const InteractingObject& interacting_object);

 protected:
  std::weak_ptr<QPixmap> image_;
  bool is_touchable_{true};
  bool delete_on_next_tick_{false};
  Type type_{Type::kNone};

  std::shared_ptr<Storage> storage_ = nullptr;

 private:
  Point coordinates_;
};

#endif  // GAMEOBJECT_OBJECT_H_
