#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <numbers>

#include "Shape.hpp"


using namespace RendMath;

class Triangle : public Shape {
public:
    // Triangle shape data? should be enough to calculate points
    Vertex center = Vertex {
        Vec3f(), Vec3f()
    };
    float circumradius = 0.5f;
    float rotation = 0.0f;

    Triangle() {}
    
    void calculateVertices() {
        // Clear vectors first
        vertices.clear();
        indices.clear();

        for (int i = 0; i < 3; i++) {
            Vertex temp;
            temp.position = Vec3f(center.position.x + circumradius * (cos(rotation + i*(2*std::numbers::pi_v<float>)/3)),
                                    center.position.y + circumradius * sin(rotation + i*(2*std::numbers::pi_v<float>)/3),
                                    0.0f);
            temp.normal = Vec3f();
            
            vertices.push_back(temp);
            indices.push_back(i);
        }
    }

    void build() {
        if (vertices.size() == 0 || indices.size() == 0) 
            calculateVertices();
        mesh = Mesh(std::move(vertices), std::move(indices));
    }

};

#endif