#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include <cmath>

#include "Mat3.hpp"
#include "Mat4.hpp"

namespace RendMath {
    template<typename T>
    class Quaternion {
    public:

        // Default constructor, initializes x, y, z, and w components to 0
        Quaternion() : x(T(0)), y(T(0)), z(T(0)), w(T(0)) {}
        // Four value constructor, initializes x, y, z, and w components
        Quaternion(T xx, T yy, T zz, T ww) : x(xx), y(yy), z(zz), w(ww) {}
        // Vec3 + w constructor
        Quaternion(Vec3<T> v, T ww) : x(v.x), y(v.y), z(v.z), w(ww) {}

        // Conversion between Quaternion types
        template<typename U>
        explicit Quaternion(const Quaternion<U>& other) : x(static_cast<T>(other.x)),
            y(static_cast<T>(other.y)), z(static_cast<T>(other.z)), w(static_cast<T>(other.w)) {}
            
        // Scalar component
        T w;
        // 'Vector' components
        T x;
        T y;
        T z;

        Mat3<T> toRotationMatrix3() const {
            return Mat3<T> {
                (T)(1 - 2*(y*y) - 2*(z*z)),
                (T)(2*x*y + 2*z*w),
                (T)(2*x*z - 2*y*w),
                (T)(2*x*y - 2*z*w),
                (T)(1 - 2*(x*x) - 2*(z*z)),
                (T)(2*y*z + 2*x*w),
                (T)(2*x*z + 2*y*w),
                (T)(2*y*z - 2*x*w),
                (T)(1 - 2*(x*x) - 2*(y*y))
            };
        }

        Mat4<T> toRotationMatrix4() const {
            return Mat4<T> {
                (T)(1 - 2*(y*y + z*z)),
                (T)(2*(x*y - z*w)),
                (T)(2*(x*z + y*w)),
                (T)(0),
                (T)(2*(x*y + z*w)),
                (T)(1 - 2*(x*x + z*z)),
                (T)(2*(y*z - x*w)),
                (T)(0),
                (T)(2*(x*z - y*w)),
                (T)(2*(y*z + x*w)),
                (T)(1 - 2*(x*x + y*y)),
                (T)(0),
                (T)(0),
                (T)(0),
                (T)(0),
                (T)(1)
            };
        }

        static Quaternion fromRotationMatrix4(const Mat4<T> m) const {
            T s, qw, qx, qy, qz = 0;
            // Calculate trace of m
            T trace = m(0,0) + m(1,1) + m(2,2) + 1;
            if (trace > T(0)) {
                s = 0.5 / (sqrt(trace));
                qw = 0.25 / s;
                qx = (m(1,2) - m(2,1)) * s;
                qy = (m(2,0) - m(0,2)) * s;
                qz = (m(0,1) - m(1,0)) * s;
            }
            else if (m(0,0) > m(1,1) && m(0,0) > m(2,2)) {
                s = sqrt(1 + m(0,0) - m(1,1) - m(2,2)) * 2;
                qx = 0.5 / s;
                qy = (m(1,0) + m(0,1)) / s;
                qz = (m(2,0) + m(0,2)) / s;
                qw = (m(2,1) + m(1,2)) / s;
            }
            else if (m(1,1) > m(0,0) && m(1,1) > m(2,2)) {
                s = sqrt(1 + m(1,1) - m(0,0) - m(2,2)) * 2;
                qx = (m(1,0) + m(0,1)) / s;
                qy = 0.5 / s;
                qz = (m(2,1) + m(1,2)) / s;
                qw = (m(2,0) + m(0,2)) / s;
            }
            else {
                s = sqrt(1 + m(2,2) - m(0,0) - m(1,1)) * 2;
                qx = (m(2,0) + m(0,2)) / s;
                qy = (m(2,1) + m(1,2)) / s;
                qz = 0.5 / s;
                qw = (m(1,0) + m(0,1)) / s;
            }
            return Quaternion(qx, qy, qz, qw);
        }

        

    private:


    };

    typedef Quaternion<float> QuaternionF;
    typedef Quaternion<double> QuaternionD;
}

#endif