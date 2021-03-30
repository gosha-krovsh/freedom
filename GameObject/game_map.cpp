#include "game_map.h"

GameMap::GameMap(std::vector<Object>* objects) :
    map_(std::vector<std::vector<std::vector<Object*>>>(
        constants::kMapMaxZ, std::vector<std::vector<Object*>>(
            constants::kMapMaxY, std::vector<Object*>(
                constants::kMapMaxX, nullptr)))) {
  for (auto& object : *objects) {
    map_[object.GetRoundedZ()]
        [object.GetRoundedY()]
        [object.GetRoundedX()] = &object;
  }
}

int GameMap::GetXSize() const {
  return map_[0][0].size();
}

int GameMap::GetYSize() const {
  return map_[0].size();
}

int GameMap::GetZSize() const {
  return map_.size();
}

const Object* GameMap::GetBlock(int x, int y, int z) const {
  if ((x < 0) || (x >= GetXSize()) ||
      (y < 0) || (y >= GetYSize()) ||
      (z < 0) || (z >= GetZSize())) {
    return nullptr;
  }
  return map_[z][y][x];
}

std::vector<const Object*> GameMap::GetCorner(int x, int y) const {
  // When there is a hall in the wall, we should consider only one wall
  if (!GetBlock(x, y, 1)) {
    if (GetBlock(x, y - 1, 1)) {
      return GetLeftWall(x, y - 1);
    } else if (GetBlock(x - 1, y, 1)) {
      return GetRightWall(x - 1, y);
    } else {
      return std::vector<const Object*>();
    }
  }

  std::vector<const Object*> result{GetLeftWall(x, y - 1)};
  auto right_wall{GetRightWall(x - 1, y)};
  result.insert(result.end(), right_wall.begin(), right_wall.end());

  // If Hero is standing right inside the corner, than 2 walls will be in the
  // |result|, but this column, that connects left and right wall - won't.
  // So we need to add it. In other cases, this code will make duplicates of
  // one of the column.
  auto current_column{GetWallColumn(x, y)};
  result.insert(result.end(), current_column.begin(), current_column.end());
  return result;
}

std::vector<const Object*> GameMap::GetLeftWall(int x, int y) const {
  int y_begin = y;
  while (y_begin > 0 &&
        !IsBlockIntersection(x, y_begin - 1, x, y_begin)) {
    --y_begin;
  }

  int y_end = y;
  while (y_end < GetYSize() &&
        !IsBlockIntersection(x, y_end + 1, x, y_end)) {
    ++y_end;
  }

  std::vector<const Object*> result;
  for (int curr_y = y_begin; curr_y <= y_end; ++curr_y) {
    auto column = GetWallColumn(x, curr_y);
    result.insert(result.end(), column.begin(), column.end());
  }
  return result;
}

std::vector<const Object*> GameMap::GetRightWall(int x, int y) const {
  int x_begin = x;
  while (x_begin > 0 &&
        !IsBlockIntersection(x_begin - 1, y, x_begin, y)) {
    --x_begin;
  }

  int x_end = x;
  while (x_end < GetXSize() &&
        !IsBlockIntersection(x_end + 1, y, x_end, y)) {
    ++x_end;
  }

  std::vector<const Object*> result;
  for (int curr_x = x_begin; curr_x <= x_end; ++curr_x) {
    auto column = GetWallColumn(curr_x, y);
    result.insert(result.end(), column.begin(), column.end());
  }
  return result;
}

bool GameMap::IsBlockIntersection(int x, int y, int prev_x, int prev_y) const {
  int delta_x = x - prev_x;
  int delta_y = y - prev_y;
  for (int curr_z = 1; curr_z < GetZSize(); ++curr_z) {
    if (GetBlock(x + delta_y, y + delta_x, curr_z) ||
        GetBlock(x - delta_y, y - delta_x, curr_z)) {
      return true;
    }
  }
  return false;
}

std::vector<const Object*> GameMap::GetWallColumn(int x, int y) const {
  std::vector<const Object*> result;
  result.reserve(GetZSize() - 1);
  for (int curr_z = 1; curr_z < GetZSize(); ++curr_z) {
    auto block = GetBlock(x, y, curr_z);
    if (block) {
      result.emplace_back(block);
    }
  }
  return result;
}
