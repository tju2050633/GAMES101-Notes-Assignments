#ifndef ROPE_H
#define ROPE_H

#include "CGL/CGL.h"
#include "mass.h"
#include "spring.h"

using namespace std;

namespace CGL {

class Rope {
public:
  // 构造函数，接受质点和弹簧的数组
  Rope(vector<Mass *> &masses, vector<Spring *> &springs)
      : masses(masses), springs(springs) {}

  // 构造函数，接受起点位置、终点位置、节点数量、节点质量、弹簧常数和固定节点的索引
  Rope(Vector2D start, Vector2D end, int num_nodes, float node_mass, float k,
       vector<int> pinned_nodes);

  // 显式 Verlet 积分模拟
  void simulateVerlet(float delta_t, Vector2D gravity);

  // 显式 Euler 积分模拟
  void simulateEuler(float delta_t, Vector2D gravity);

  vector<Mass *> masses;    // 质点数组
  vector<Spring *> springs; // 弹簧数组
}; // class Rope
}
#endif /* ROPE_H */
