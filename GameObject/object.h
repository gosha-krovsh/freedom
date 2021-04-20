#ifndef GAMEOBJECT_OBJECT_H_
#define GAMEOBJECT_OBJECT_H_

#include <QPainter>

#include <memory>

#include "Model/constants.h"
#include "point.h"
#include "interacting_object.h"

class Object {
 public:
  enum class ObjectType {
    kNone,
    kWall
  };

 public:
  explicit Object(const Point& coords,
                  const std::weak_ptr<QPixmap>& image =
                      std::weak_ptr<QPixmap>());
  virtual ~Object() = default;

  virtual void Tick(int current_time);

  Point GetCoordinates() const;
  double GetX() const;
  double GetY() const;
  double GetZ() const;
  int GetRoundedX() const;
  int GetRoundedY() const;
  int GetRoundedZ() const;
  void SetCoordinates(const Point& coords);
  void SetX(double x);
  void SetY(double y);
  void SetZ(double z);

  bool IsTouchable() const;
  bool IsType(ObjectType object_type) const;
  bool ToDelete() const;

  void Draw(QPainter* painter) const;
  virtual void Interact(const InteractingObject& interacting_object);

 protected:
  std::weak_ptr<QPixmap> image_;
  bool is_touchable_{true};
  bool delete_on_next_tick_{false};
  ObjectType type_{ObjectType::kNone};

 private:
  Point coordinates_;
};

#endif  // GAMEOBJECT_OBJECT_H_
