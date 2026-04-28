#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <numbers>

#include "Shape.hpp"


using namespace RendMath;

class Circle : public Shape {
public:
    // Circle shape data
    Vertex center = Vertex {
        Vec3f(), Vec3f(1.0f)
    };
    unsigned int numSides = 8;
    float circumradius = 0.5f;
    float rotation = 0.0f;

    Circle() {}
    
    void calculateVertices() {
        // Clear vectors first
        vertices.clear();
        indices.clear();

        vertices.push_back(center);

        for (unsigned int i = 0; i < numSides+1; i++) {
            Vertex temp;
            temp.position = Vec3f(center.position.x + circumradius * (cos(rotation + i*(2*std::numbers::pi_v<float>)/numSides)),
                                    center.position.y + circumradius * sin(rotation + i*(2*std::numbers::pi_v<float>)/numSides),
                                    0.0f);
            temp.normal = Vec3f(i==0, i==1, i==2);
            
            vertices.push_back(temp);
            if (i >= 2) {
                indices.insert(indices.end(), {0, i-1, i});
            }
        }
        // Fill in gap
        indices.insert(indices.end(), {0, 1, numSides});
    }

    void build() {
        if (vertices.size() == 0 || indices.size() == 0) 
            calculateVertices();
        mesh = Mesh(std::move(vertices), std::move(indices));
    }

};

#endif