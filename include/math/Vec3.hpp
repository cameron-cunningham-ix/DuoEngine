#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <cassert>
#include <stdexcept>

namespace RendMath{
    template<typename T>
    class Vec3 {
    public:
        // Default constructor, initializes x, y, and z components to 0
        Vec3() : x(T(0)), y(T(0)), z(T(0)) {}
        // Single value constructor, initializes x, y, and components to the same value
        Vec3(T xx) : x(xx), y(xx), z(xx) {}
        // Three value constructor, initializes x, y, and z components
        Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}
        // Conversion
        template<typename U>
        explicit Vec3(const Vec3<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z)) {}

        T x;
        T y;
        T z;
    
        // Returns the vector's length
        T length() const {
            static_assert(std::is_floating_point_v<T>, "Vec3<T>.length() only supported for float and double types.");
            return std::sqrt(x * x + y * y + z * z);
        }
    
        // Normalize this vector
        Vec3<T>& normalize() {
            static_assert(std::is_floating_point_v<T>, "Vec3<T>.normalize() only supported for float and double types.");
            T len = dot(*this); // Using dot() instead of length() so that if this is 0 we can skip sqrt call cost
            if (len > 0) {
                T inverse_length = T(1) / std::sqrt(len);
                x *= inverse_length; y *= inverse_length; z *= inverse_length;
            }
            return *this;
        }
    
        // Returns the dot product of this vector and vector v
        T dot(const Vec3<T>& v) const {
            return x * v.x + y * v.y + z * v.z;
        }

        // Cross product of this vector and vector v
        Vec3<T> cross(const Vec3<T>& v) const {
            return Vec3<T>((y * v.z - z * v.y), (z * v.x - x * v.z), (x * v.y - y * v.x));
        }

        Vec3<T>& lerp(const Vec3<T>& v, double distance) {
            static_assert(std::is_floating_point_v<T>, "Vec3<T>.lerp() only supported for float and double types.");
            x = x + (v.x - x) * distance; y = y + (v.y - y) * distance; z = z + (v.z - z) * distance;
            return *this;
        }

        bool approxEq(const Vec3<T>& b, T epsilon) const {
            return std::abs(x - b.x) <= epsilon && std::abs(y - b.y) <= epsilon && std::abs(z - b.z) <= epsilon;
        }
    
        T operator[] (size_t index) const {
            if (index == 0) return x;
            else if (index == 1) return y;
            else if (index == 2) return z;
            else throw std::out_of_range("Vec3 index out of range");
        }
        
        T& operator[] (size_t index) {
            if (index == 0) return x;
            else if (index == 1) return y;
            else if (index == 2) return z;
            else throw std::out_of_range("Vec3 index out of range");
        }

        Vec3<T> operator + (const Vec3<T>& v) const {
            return Vec3<T>(x + v.x, y + v.y, z + v.z);
        }
    
        Vec3<T>& operator += (const Vec3<T>& v) {
            x += v.x; y += v.y; z += v.z;
            return *this;
        }
    
        Vec3<T> operator - (const Vec3<T>& v) const {
            return Vec3<T>(x - v.x, y - v.y, z - v.z);
        }
    
        Vec3<T>& operator -= (const Vec3<T>& v) {
            x -= v.x; y -= v.y; z -= v.z;
            return *this;
        }
    
        Vec3<T> operator * (const T& t) const {
            return Vec3<T>(x * t, y * t, z * t);
        }
    
        Vec3<T>& operator *= (const T& t) {
            x *= t; y *= t; z *= t;
            return *this;
        }
    
        Vec3<T> operator * (const Vec3<T>& v) const {
            return Vec3<T>(x * v.x, y * v.y, z * v.z);
        }
    
        Vec3<T>& operator *= (const Vec3<T>& v) {
            x *= v.x; y *= v.y; z *= v.z;
            return *this;
        }
    
        // TODO: change asserts to throws. Dont know why I thought to make them asserts
        Vec3<T> operator / (const T& t) const {
            assert(t != T(0));
            return Vec3<T>(x / t, y / t, z / t);
        }
    
        Vec3<T>& operator /= (const T& t) {
            assert(t != T(0));
            x /= t; y /= t; z /= t;
            return *this;
        }
    
        Vec3<T> operator / (const Vec3<T>& v) const {
            assert(v.x != T(0) && v.y != T(0) && v.z != T(0));
            return Vec3<T>(x / v.x, y / v.y, z / v.z);
        }
    
        Vec3<T>& operator /= (const Vec3<T>& v) {
            assert(v.x != T(0) && v.y != T(0) && v.z != T(0));
            x /= v.x; y /= v.y; z /= v.z;
            return *this;
        }
    
        // Negation: v * -1
        Vec3<T> operator- () const {
            return Vec3<T>(-x, -y, -z);
        }
    
        // NOTE: == on floats / doubles is for exact equality. For math comparisons use approxEq instead
        bool operator== (const Vec3<T>& b) const {
            return (x == b.x && y == b.y && z == b.z);
        }
    
        // NOTE: != on floats / doubles is for exact equality. For math comparisons use approxEq instead
        bool operator!= (const Vec3<T>& b) const {
            return (x != b.x || y != b.y || z != b.z);
        }
    
    };
    
    typedef Vec3<int> Vec3i;
    typedef Vec3<float> Vec3f;
    typedef Vec3<double> Vec3d;
    
    // Returns the vector's length
    template<typename T>
    T length(const Vec3<T> &v) {
        static_assert(std::is_floating_point_v<T>, "Vec3<T>.length() only supported for float and double types.");
        return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }
    
    // Returns the dot product of vector a and vector b
    template<typename T>
    T dot(const Vec3<T> &a, const Vec3<T> &b) {
        return (a.x * b.x + a.y * b.y + a.z * b.z);
    }
    
    // Normalize this vector
    template<typename T>
    Vec3<T> normalize(const Vec3<T> &v) {
        static_assert(std::is_floating_point_v<T>, "Vec3<T>.normalize() only supported for float and double types.");
        // Using dot() instead of length() so that if this is 0 we can also skip sqrt call cost
        T length = dot(v, v);
        if (length > 0) {
            T inverse_length = T(1) / std::sqrt(length);
            return Vec3<T>(v.x * inverse_length, v.y * inverse_length, v.z * inverse_length);
        }
        return v;
    }

    // Cross product of this vector and vector v
    template<typename T>
    Vec3<T> cross(const Vec3<T>& v, const Vec3<T>& w) {
        return Vec3<T>((v.y * w.z - v.z * w.y), (v.z * w.x - v.x * w.z), (v.x * w.y - v.y * w.x));
    }

    template<typename T>
    Vec3<T> lerp(const Vec3<T>& v, const Vec3<T>& w, double distance) {
        static_assert(std::is_floating_point_v<T>, "Vec3<T>.lerp() only supported for float and double types.");
        return Vec3<T>(v.x + (w.x - v.x) * distance, v.y + (w.y - v.y) * distance, v.z + (w.z - v.z) * distance);
    }
    
    template<typename T>
    bool approxEq(const Vec3<T>& a, const Vec3<T>& b, T epsilon) {
        return std::abs(a.x - b.x) <= epsilon && std::abs(a.y - b.y) <= epsilon && std::abs(a.z - b.z) <= epsilon;
    }
    
    template<typename T>
    Vec3<T> operator*(T t, const Vec3<T>& v) {
        return Vec3<T>(v.x * t, v.y * t, v.z * t);
    }
}


#endif