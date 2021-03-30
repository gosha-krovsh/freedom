#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include <vector>

#include "object.h"

class GameMap {
 public:
  GameMap() = default;
  explicit GameMap(std::vector<Object>* objects);

  int GetXSize() const;
  int GetYSize() const;
  int GetZSize() const;

  // override operator []
  const Object* GetBlock(int x, int y, int z) const;
  std::vector<const Object*> GetCorner(int x, int y) const;

 private:
  bool IsBlockIntersection(int x, int y, int prev_x, int prev_y) const;
  std::vector<const Object*> GetLeftWall(int x, int y) const;
  std::vector<const Object*> GetRightWall(int x, int y) const;
  std::vector<const Object*> GetWallColumn(int x, int y) const;

 private:
  std::vector<std::vector<std::vector<Object*>>> map_;
};

#endif  // GAME_MAP_H_
