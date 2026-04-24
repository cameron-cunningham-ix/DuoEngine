#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "math/Vec3.hpp"

struct Vertex {
    RendMath::Vec3<float> position;
    RendMath::Vec3<float> normal;
};

#endif