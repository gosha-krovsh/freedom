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

  const Object* GetBlock(int x, int y, int z) const;

  // Returns together left and(or) right walls of (x, y) blocks.
  std::vector<const Object*> GetCorner(int x, int y) const;

 private:
  // Returns the left (i.e. going in |y| direction) wall of blocks, where
  // (x, y) is situated.
  std::vector<const Object*> GetLeftWall(int x, int y) const;

  // Returns the right (i.e. going in |x| direction) wall of blocks, where
  // (x, y) is situated.
  std::vector<const Object*> GetRightWall(int x, int y) const;

  // Returns true, if when going in (prev_x, prev_y)->(x, y) direction
  // (on any height) the orthogonal line of block crosses our direction in
  // (x, y) point, i.e. there is the intersection of 2 orthogonal lines.
  // Pay attention: there can be no block in (prev_x, prev_y)! It's just the
  // direction.
  bool IsBlockIntersection(int x, int y, int prev_x, int prev_y) const;

  // Returns all blocks, except floor, which are situated in (x, y).
  // So all (x, y, z_i), where (z_i != 0)
  std::vector<const Object*> GetWallColumn(int x, int y) const;

 private:
  std::vector<std::vector<std::vector<Object*>>> map_;
};

#endif  // GAME_MAP_H_
