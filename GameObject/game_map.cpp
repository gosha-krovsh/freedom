#include "game_map.h"

GameMap::Room::Room(const QString& name,
                    int bottom_left_x, int bottom_left_y,
                    int up_right_x, int up_right_y) :
    name(name),
    down_left_x(bottom_left_x), down_left_y(bottom_left_y),
    up_right_x(up_right_x), up_right_y(up_right_y) {
  if (bottom_left_x <= up_right_x) {
    qDebug() << "In constructing room: |down_left_x| <= |up_right_x|";
  }
  if (bottom_left_y >= up_right_y) {
    qDebug() << "In constructing room: |down_left_y| <= |up_right_y|";
  }
}

bool GameMap::Room::IsInside(int x, int y) const {
  return (x < down_left_x &&
          x > up_right_x &&
          y > down_left_y &&
          y < up_right_y);
}

bool GameMap::Room::IsInsideOrOnTheEdge(int x, int y) const {
  return (x <= down_left_x &&
          x >= up_right_x &&
          y >= down_left_y &&
          y <= up_right_y);
}

bool GameMap::Room::operator==(const GameMap::Room& rhs) const {
  return (name == rhs.name) &&
         (down_left_x == rhs.down_left_x) &&
         (down_left_y == rhs.down_left_y) &&
         (up_right_x == rhs.up_right_x) &&
         (up_right_y == rhs.up_right_y);
}

bool GameMap::Room::operator!=(const GameMap::Room& rhs) const {
  return !(*this == rhs);
}

bool GameMap::Room::IsOnTheEdge(int x, int y) const {
  return (IsInsideOrOnTheEdge(x, y) && !IsInside(x, y));
}

bool GameMap::Room::IsInside(const Room& room) const {
  return (IsInsideOrOnTheEdge(room.down_left_x, room.down_left_y) &&
          IsInsideOrOnTheEdge(room.up_right_x, room.up_right_y));
}

// ----------------------------------------------------------------------------

GameMap::GameMap(int x_size, int y_size, int z_size,
                 const std::vector<Object*>& objects,
                 const std::vector<Room>& rooms,
                 int hero_z) :
                 map_(std::vector<std::vector<std::vector<Object*>>>(
                            z_size, std::vector<std::vector<Object*>>(
                                x_size, std::vector<Object*>(
                                    y_size, nullptr)))),
                 rooms_(rooms),
                 hero_z_(hero_z) {
  for (auto& object : objects) {
    if (object) {
      map_[object->GetRoundedZ()]
          [object->GetRoundedX()]
          [object->GetRoundedY()] = object;
    }
  }
  // Otherwise, won't be updated after a tick, if hero will be in the 1 room.
  UpdateTransparentBlocks();
}

GameMap::~GameMap() {
  for (auto& surface : map_) {
    for (auto& line : surface) {
      for (auto& block : line) {
        delete block;
      }
    }
  }
}

void GameMap::Tick(int current_tick) {
  for (auto& plane : map_) {
    for (auto& line : plane) {
      for (auto& block : line) {
        if (block == nullptr) {
          continue;
        }

        block->Tick(current_tick);

        if (block->ToDelete()) {
          delete block;
          block = nullptr;
        }
      }
    }
  }
}

int GameMap::GetXSize() const {
  return map_[0].size();
}

int GameMap::GetYSize() const {
  return map_[0][0].size();
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
  return map_[z][x][y];
}
Object* GameMap::GetBlock(int x, int y, int z) {
  if ((x < 0) || (x >= GetXSize()) ||
      (y < 0) || (y >= GetYSize()) ||
      (z < 0) || (z >= GetZSize())) {
    return nullptr;
  }
  return map_[z][x][y];
}

std::unordered_set<const Object*> GameMap::GetTransparentBlocks() const {
  return transparent_blocks_;
}

void GameMap::UpdateCurrentRoom(int hero_x, int hero_y) {
  auto edge_room_iter = GetEdgeRoom(hero_x, hero_y);
  if (edge_room_iter != rooms_.end()) {
    if (!is_hero_on_the_room_edge_) {
      is_hero_on_the_room_edge_ = true;
      current_room_ = *edge_room_iter;
      UpdateTransparentBlocks();
    }
  } else {
    is_hero_on_the_room_edge_ = false;
    current_room_ = GetMostInnerRoom(hero_x, hero_y);
    UpdateTransparentBlocks();
  }
}

GameMap::Room GameMap::GetMostInnerRoom(int hero_x, int hero_y) const {
  Room result = rooms_.at(0);
  for (const auto& room : rooms_) {
    if (room.IsInsideOrOnTheEdge(hero_x, hero_y) &&
       (!result.IsInsideOrOnTheEdge(hero_x, hero_y) || result.IsInside(room))) {
      result = room;
    }
  }
  return result;
}

std::vector<GameMap::Room>::const_iterator
    GameMap::GetEdgeRoom(int hero_x, int hero_y) const {
  return std::find_if(rooms_.begin(), rooms_.end(),
                      [hero_x, hero_y, this](const Room& room) {
    return (room != current_room_) && (room.IsOnTheEdge(hero_x, hero_y) || (
               current_room_.IsOnTheEdge(hero_x, hero_y) &&
               room.IsInside(current_room_)));
  });
}

std::vector<const Object*> GameMap::GetWallColumn(int x, int y) const {
  std::vector<const Object*> result;
  result.reserve(GetZSize() - hero_z_);
  for (int curr_z = hero_z_; curr_z < GetZSize(); ++curr_z) {
    auto block = GetBlock(x, y, curr_z);
    if (block) {
      result.emplace_back(block);
    }
  }
  return result;
}

void GameMap::UpdateTransparentBlocks() {
  transparent_blocks_.clear();
  for (int x = current_room_.up_right_x + 1;
       x <= current_room_.down_left_x; ++x) {
    auto column = GetWallColumn(x, current_room_.up_right_y);
    transparent_blocks_.insert(column.begin(), column.end());
  }
  for (int y = current_room_.down_left_y + 1;
       y < current_room_.up_right_y; ++y) {
    auto column = GetWallColumn(current_room_.down_left_x, y);
    transparent_blocks_.insert(column.begin(), column.end());
  }
}
