#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Mesh.hpp"

/// @brief Abstract base class for mesh shapes
class Shape {
public:

    Mesh mesh;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    virtual void calculateVertices() = 0;
    virtual void build() = 0;
    Shape() {}
    virtual ~Shape() {}

};

#endif