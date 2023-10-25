#ifndef MASS_H
#define MASS_H

#include "CGL/CGL.h"
#include "CGL/vector2D.h"

using namespace CGL;

struct Mass {
  Mass(Vector2D position, float mass, bool pinned)
      : start_position(position), position(position), last_position(position),
        mass(mass), pinned(pinned) {}

  float mass;         // 质量
  bool pinned;        // 是否固定不动

  Vector2D start_position;  // 初始位置
  Vector2D position;         // 当前位置

  // 显式 Verlet 积分

  Vector2D last_position;    // 上一个位置

  // 显式 Euler 积分

  Vector2D velocity;         // 速度
  Vector2D forces;           // 受力
};

#endif /* MASS_H */
