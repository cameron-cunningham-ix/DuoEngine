#ifndef VEC2_HPP
#define VEC2_HPP

#include <cmath>
#include <cassert>

namespace RendMath{
    template<typename T>
    class Vec2 {
    public:
        // Default constructor, initializes x and y components to 0
        Vec2() : x(T(0)), y(T(0)) {}
        // Single value constructor, initializes x and y components to the same value
        Vec2(T xx) : x(xx), y(xx) {}
        // Two value constructor, initializes x and y components to first and second parameters respectively
        Vec2(T xx, T yy) : x(xx), y(yy) {}
        T x;
        T y;
    
        // Returns the vector's length
        T length() const {
            static_assert(std::is_floating_point_v<T>, "Vec2<T>.length() only supported for float and double types.");
            return std::sqrt(x * x + y * y);
        }
    
        // Normalize this vector
        Vec2<T>& normalize() {
            static_assert(std::is_floating_point_v<T>, "Vec2<T>.normalize() only supported for float and double types.");
            T len = dot(*this); // Using dot() instead of length() so that if this is 0 we can skip sqrt call cost
            if (len > 0) {
                T inverse_length = T(1) / std::sqrt(len);
                x *= inverse_length; y *= inverse_length;
            }
            return *this;
        }
    
        // Returns the dot product of this vector and vector v
        T dot(const Vec2<T>& v) const {
            return x * v.x + y * v.y;
        }

        // Lerp: Linear Enterpolation
        // distance: 0 to 1 - distance to vector v, 0 being at this vector, 1 being at vector v
        Vec2<T>& lerp(const Vec2<T>& v, double distance) {
            static_assert(std::is_floating_point_v<T>, "Vec2<T>.lerp() only supported for float and double types.");
            x = x + (v.x - x) * distance; y = y + (v.y - y) * distance;
            return *this;
        }

        bool approxEq(const Vec2<T>& b, T epsilon) const {
            return std::abs(x - b.x) <= epsilon && std::abs(y - b.y) <= epsilon;
        }
    
        T operator[] (size_t index) const {
            if (index == 0) return x;
            else if (index == 1) return y;
            else throw std::out_of_range("Vec2 index out of range");
        }
    
        Vec2<T> operator + (const Vec2<T>& v) const {
            return Vec2<T>(x + v.x, y + v.y);
        }
    
        Vec2<T>& operator += (const Vec2<T>& v) {
            x += v.x; y += v.y;
            return *this;
        }
    
        Vec2<T> operator - (const Vec2<T>& v) const {
            return Vec2<T>(x - v.x, y - v.y);
        }
    
        Vec2<T>& operator -= (const Vec2<T>& v) {
            x -= v.x; y -= v.y;
            return *this;
        }
    
        Vec2<T> operator * (const T& t) const {
            return Vec2<T>(x * t, y * t);
        }
    
        Vec2<T>& operator *= (const T& t) {
            x *= t; y *= t;
            return *this;
        }
    
        Vec2<T> operator * (const Vec2<T>& v) const {
            return Vec2<T>(x * v.x, y * v.y);
        }
    
        Vec2<T>& operator *= (const Vec2<T>& v) {
            x *= v.x; y *= v.y;
            return *this;
        }
    
        Vec2<T> operator / (const T& t) const {
            assert(t != T(0));
            return Vec2<T>(x / t, y / t);
        }
    
        Vec2<T>& operator /= (const T& t) {
            assert(t != T(0));
            x /= t; y /= t;
            return *this;
        }
    
        Vec2<T> operator / (const Vec2<T>& v) const {
            assert(v.x != T(0) && v.y != T(0));
            return Vec2<T>(x / v.x, y / v.y);
        }
    
        Vec2<T>& operator /= (const Vec2<T>& v) {
            assert(v.x != T(0) && v.y != T(0));
            x /= v.x; y /= v.y;
            return *this;
        }
    
        // Negation: v * -1
        Vec2<T> operator- () const {
            return Vec2<T>(-x, -y);
        }
    
        // NOTE: == on floats / doubles is for exact equality. For math comparisons use approxEq instead
        bool operator== (const Vec2<T>& b) const {
            return (x == b.x && y == b.y);
        }
    
        // NOTE: != on floats / doubles is for exact equality. For math comparisons use approxEq instead
        bool operator!= (const Vec2<T>& b) const {
            return (x != b.x || y != b.y);
        }
    
    };
    
    typedef Vec2<int> Vec2i;
    typedef Vec2<float> Vec2f;
    typedef Vec2<double> Vec2d;
    
    // Returns the vector's length
    template<typename T>
    T length(const Vec2<T> &v) {
        static_assert(std::is_floating_point_v<T>, "Vec2<T>.length() only supported for float and double types.");
        return std::sqrt(v.x * v.x + v.y * v.y);
    }
    
    // Returns the dot product of vector a and vector b
    template<typename T>
    T dot(const Vec2<T> &a, const Vec2<T> &b) {
        return (a.x * b.x + a.y * b.y);
    }
    
    // Normalize this vector
    template<typename T>
    Vec2<T> normalize(const Vec2<T> &v) {
        static_assert(std::is_floating_point_v<T>, "Vec2<T>.normalize() only supported for float and double types.");
        // Using dot() instead of length() so that if this is 0 we can also skip sqrt call cost
        T length = dot(v, v);
        if (length > 0) {
            T inverse_length = T(1) / std::sqrt(length);
            return Vec2<T>(v.x * inverse_length, v.y * inverse_length);
        }
        return v;
    }

    template<typename T>
    Vec2<T> lerp(const Vec2<T>& v, const Vec2<T>& w, double distance) {
        static_assert(std::is_floating_point_v<T>, "Vec2<T>.lerp() only supported for float and double types.");
        return Vec2<T>(v.x + (w.x - v.x) * distance, v.y + (w.y - v.y) * distance);
    }
    
    template<typename T>
    bool approxEq(const Vec2<T>& a, const Vec2<T>& b, T epsilon) {
        return std::abs(a.x - b.x) <= epsilon && std::abs(a.y - b.y) <= epsilon;
    }
    
    template<typename T>
    Vec2<T> operator*(T t, const Vec2<T>& v) {
        return Vec2<T>(v.x * t, v.y * t);
    }
}


#endif