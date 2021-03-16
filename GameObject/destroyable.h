#ifndef GAMEOBJECT_DESTROYABLE_H_
#define GAMEOBJECT_DESTROYABLE_H_

class Destroyable {
 public:
  explicit Destroyable(int max_hp);

  bool IsDestroyed() const;
  int GetHP() const;

  void IncreaseHP(int hp);
  void DecreaseHP(int hp);

  virtual void OnDead() = 0;

 private:
  int max_hp_;
  int hp_;
};

#endif  // GAMEOBJECT_DESTROYABLE_H_
