#include <iostream>
#include <vector>

#include "CGL/vector2D.h"

#include "mass.h"
#include "rope.h"
#include "spring.h"

namespace CGL {

    Rope::Rope(Vector2D start, Vector2D end, int num_nodes, float node_mass, float k, vector<int> pinned_nodes)
    {
        // TODO (Part 1): Create a rope starting at `start`, ending at `end`, and containing `num_nodes` nodes.

//        Comment-in this part when you implement the constructor
//        for (auto &i : pinned_nodes) {
//            masses[i]->pinned = true;
//        }

        // 错误检查
        if (num_nodes < 3)
        {
            std::cerr << "Error: too few nodes specified for rope." << std::endl;
            exit(1);
        }

        // 分配内存
        Mass* masses = new Mass[num_nodes];
        Spring* springs = new Spring[num_nodes - 1];

        // 创建质点
        for(int i = 0; i < num_nodes; i++)
        {
            Mass mass = new Mass(start + (end - start) * i / (num_nodes - 1), node_mass, false);
            memcpy(masses + i, &mass, sizeof(Mass));
        }

        // 设置pinned
        for (auto &i : pinned_nodes) {
            masses[i]->pinned = true;
        }

        // 创建弹簧
        for(int i = 0; i < num_nodes - 1; i++)
        {
            Spring spring = new Spring(masses[i], masses[i + 1], k);
            memcpy(springs + i, &spring, sizeof(Spring));
        }

        // 保存质点和弹簧数组
        this->masses = masses;
        this->springs = springs;
    }

    void Rope::simulateEuler(float delta_t, Vector2D gravity)
    {
        for (auto &s : springs)
        {
            // TODO (Part 2): Use Hooke's law to calculate the force on a node
            
            // 弹簧当前长度
            float d = (s->m1->position - s->m2->position).norm();

            // 单位向量
            Vector2D u = (s->m1->position - s->m2->position).unit();

            // 弹簧受力
            Vector2D f = -s->k * (d - s->rest_length) * u;

            // 质点受力
            s->m1->forces += f;
            s->m2->forces -= f;
        }

        for (auto &m : masses)
        {
            if (!m->pinned)
            {
                Vector2D temp_position = m->position;
                // TODO (Part 2): Add the force due to gravity, then compute the new velocity and position
                m->forces += gravity * m->mass;                 // 重力

                // m->position += m->velocity * delta_t;           // x(t+1) = x(t) + v(t) * dt for explicit method
                // m->velocity += m->forces / m->mass * delta_t;   // v(t+1) = v(t) + a(t) * dt

                m->velocity += m->forces / m->mass * delta_t;   // v(t+1) = v(t) + a(t) * dt
                m->position += m->velocity * delta_t;           // x(t+1) = x(t) + v(t) * dt for semi-implicit method

                // TODO (Part 2): Add global damping

                m->last_position = temp_position;
            }

            // Reset all forces on each mass
            m->forces = Vector2D(0, 0);
        }
    }

    void Rope::simulateVerlet(float delta_t, Vector2D gravity)
    {
        for (auto &s : springs)
        {
            // TODO (Part 3): Simulate one timestep of the rope using explicit Verlet （solving constraints)

            // 弹簧当前长度
            float d = (s->m1->position - s->m2->position).norm();

            // 单位向量
            Vector2D u = (s->m1->position - s->m2->position).unit();

            // 弹簧受力
            Vector2D f = -s->k * (d - s->rest_length) * u;

            // 质点受力
            s->m1->forces += f;
            s->m2->forces -= f;
        }

        for (auto &m : masses)
        {
            if (!m->pinned)
            {
                Vector2D temp_position = m->position;           // x(t)
                Vector2D temp_last_position = m->last_position; // x(t-1)

                // TODO (Part 3.1): Set the new position of the rope mass
                m->forces += gravity * m->mass;                 // 重力
                m->position = temp_position * 2 - temp_last_position + m->forces / m->mass * delta_t * delta_t;   // x(t+1) = 2 * x(t) - x(t-1) + a(t) * dt^2
                
                // TODO (Part 4): Add global Verlet damping
                m->position += (1 - 0.00005) * (temp_position - temp_last_position) + m->forces / m->mass * delta_t * delta_t;  // x(t+1) = x(t) + (1 - damping) * (x(t) - x(t-1)) + a(t) * dt^2

                m->last_position = temp_position;
            }
        }
    }
}
