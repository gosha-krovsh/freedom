#ifndef GAMEOBJECT_INTERACTING_OBJECT_H_
#define GAMEOBJECT_INTERACTING_OBJECT_H_

class InteractingObject {
 public:
  virtual double GetX() const = 0;
  virtual double GetY() const = 0;
  virtual int GetRoundedX() const = 0;
  virtual int GetRoundedY() const = 0;
  virtual int GetAttack() const = 0;
};

#endif  // GAMEOBJECT_INTERACTING_OBJECT_H_
