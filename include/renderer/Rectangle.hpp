#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <numbers>

#include "Shape.hpp"


using namespace RendMath;

class Rectangle : public Shape {
public:
    // Rectangle shape data
    Vertex center = Vertex {
        Vec3f(), Vec3f()
    };
    float sideLengthTop = 0.5f;
    float sideLengthRight = 0.5f;
    // float rotation = 0.0f;

    Rectangle() {}
    
    void calculateVertices() {
        // Clear vectors first
        vertices.clear();
        indices.clear();

        Vertex tl;
        tl.position = Vec3f(center.position.x - sideLengthTop/2.0f,
                            center.position.y - sideLengthRight/2.0f,
                            0.0f);
        tl.normal = Vec3f(1.0f, 0.0f, 0.0f);
        Vertex tr;
        tr.position = Vec3f(center.position.x + sideLengthTop/2.0f,
                            center.position.y - sideLengthRight/2.0f,
                            0.0f);
        tr.normal = Vec3f(0.0f, 1.0f, 0.0f);
        Vertex bl;
        bl.position = Vec3f(center.position.x - sideLengthTop/2.0f,
                            center.position.y + sideLengthRight/2.0f,
                            0.0f);
        bl.normal = Vec3f(0.0f, 0.0f, 1.0f);
        Vertex br;
        br.position = Vec3f(center.position.x + sideLengthTop/2.0f,
                            center.position.y + sideLengthRight/2.0f,
                            0.0f);
        br.normal = Vec3f(1.0f, 1.0f, 1.0f);
        
        vertices.insert(vertices.end(), {tl, tr, bl, br});
        indices.insert(indices.end(), {0, 1, 2, 1, 2, 3});
    }

    void build() {
        if (vertices.size() == 0 || indices.size() == 0) 
            calculateVertices();
        mesh = Mesh(std::move(vertices), std::move(indices));
    }

};

#endif