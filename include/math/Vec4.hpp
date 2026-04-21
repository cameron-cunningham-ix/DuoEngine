#ifndef VEC4_HPP
#define VEC4_HPP

#include <stdexcept>

#include "Vec3.hpp"

namespace RendMath{
    template<typename T>
    class Vec4 {
    public:
        // Default constructor, initializes x, y, z, and w components to 0
        Vec4() : x(T(0)), y(T(0)), z(T(0)), w(T(0)) {}
        // Four value constructor, initializes x, y, z, and w components
        Vec4(T xx, T yy, T zz, T ww) : x(xx), y(yy), z(zz), w(ww) {}
        // Vec3 + w constructor
        Vec4(Vec3<T> v, T ww) : x(v.x), y(v.y), z(v.z), w(ww) {}

        // Conversion between Vec4 types
        template<typename U>
        explicit Vec4(const Vec4<U>& other) : x(static_cast<T>(other.x)),
            y(static_cast<T>(other.y)), z(static_cast<T>(other.z)), w(static_cast<T>(other.w)) {}

        T x;
        T y;
        T z;
        T w;
    
        T operator[] (size_t index) const {
            if (index == 0) return x;
            else if (index == 1) return y;
            else if (index == 2) return z;
            else if (index == 3) return w;
            else throw std::out_of_range("Vec4 index out of range");
        }
    
        // NOTE: == on floats / doubles is for exact equality. For math comparisons use approxEq instead
        bool operator== (const Vec4<T>& b) const {
            return (x == b.x && y == b.y && z == b.z && w == b.w);
        }
    
        // NOTE: != on floats / doubles is for exact equality. For math comparisons use approxEq instead
        bool operator!= (const Vec4<T>& b) const {
            return (x != b.x || y != b.y || z != b.z || w != b.w);
        }
    
    };
    
    typedef Vec4<int> Vec4i;
    typedef Vec4<float> Vec4f;
    typedef Vec4<double> Vec4d;
    
    template<typename T>
    Vec3<T> toVec3(const Vec4<T>& v) {
        if (v.w == T(0)) return Vec3<T>(v.x, v.y, v.z);
        return Vec3<T>(v.x / v.w, v.y / v.w, v.z / v.w);
    }
}


#endif