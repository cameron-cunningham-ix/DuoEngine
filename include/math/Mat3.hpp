#ifndef MAT3_HPP
#define MAT3_HPP

#include <cmath>
#include <cassert>
#include <array>
#include <utility>
#include <stdexcept>

#include "Vec3.hpp"

namespace RendMath{
    template<typename T>
    class Mat3 {
    public:
        // Identity constructor
        Mat3() {
            m = {1, 0, 0, 0, 1, 0, 0, 0, 1};
        }
        // 9 value constructor; parameters are in row-major order, and get stored as column-major order
        Mat3(T a, T b, T c, T d, T e, T f, T g, T h, T i) {
            m = {a, d, g, b, e, h, c, f, i};
        }
        // Column-major layout
        std::array<T, 9> m;

        T& operator()(int row, int col) {
            return m[col * 3 + row];
        }
        
        T operator()(int row, int col) const {
            return m[col * 3 + row];
        }

        // Matrix multiplication
        Mat3<T> operator*(const Mat3<T>& a) const {
            Mat3<T> result;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    result(j, i) = (*this)(j, 0) * a(0, i) + (*this)(j, 1) * a(1, i) + (*this)(j, 2) * a(2, i);
                }
            }
            return result;
        }
        
        // Scalar multiplication
        Mat3<T> operator*(const T& scalar) const {
            Mat3<T> result;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    result(j, i) = (*this)(j, i) * scalar;
                }
            }
            return result;
        }
        
        Mat3<T>& operator*=(const T& scalar) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    (*this)(j, i) *= scalar;
                }
            }
            return *this;
        }

        // Vector multiplication
        Vec3<T> operator*(const Vec3<T>& v) const {
            Vec3<T> result;
            for (int i = 0; i < 3; i++) {
                result[i] = v[0] * (*this)(i, 0) + v[1] * (*this)(i, 1) + v[2] * (*this)(i, 2);
            }
            return result;
        }

        bool operator==(const Mat3<T>& a) const {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (a(j,i) != (*this)(j,i)) return false;
                }
            }
            return true;
        }

        Mat3<T> transpose() const {
            Mat3<T> result;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    result(j, i) = (*this)(i, j);
                }
            }
            return result;
        }

        Mat3<T>& transposeInPlace() {
            std::swap((*this)(1,0), (*this)(0,1));
            std::swap((*this)(2,0), (*this)(0,2));
            std::swap((*this)(1,2), (*this)(2,1));

            return *this;
        }

        T determinant() const {
            return (
                (*this)(0,0) * ((*this)(1,1)*(*this)(2,2) - (*this)(1,2)*(*this)(2,1)) -
                (*this)(0,1) * ((*this)(1,0)*(*this)(2,2) - (*this)(1,2)*(*this)(2,0)) +
                (*this)(0,2) * ((*this)(1,0)*(*this)(2,1) - (*this)(1,1)*(*this)(2,0))
            );
        }

        //  m(0,0)  m(0,1)  m(0,2)
        //  m(1,0)  m(1,1)  m(1,2)
        //  m(2,0)  m(2,1)  m(2,2)

        Mat3<T> inverse() const {
            T det = determinant();
            if (det == T(0)) throw std::runtime_error("non-invertible matrix");
            T inv_det = T(1) / det;

            Mat3<T> inverse = {
                inv_det * ((*this)(1,1) * (*this)(2,2) - (*this)(2,1) * (*this)(1,2)),
                inv_det * (-((*this)(0,1) * (*this)(2,2) - (*this)(2,1) * (*this)(0,2))),
                inv_det * ((*this)(0,1) * (*this)(1,2) - (*this)(1,1) * (*this)(0,2)),

                inv_det * (-((*this)(1,0) * (*this)(2,2) - (*this)(2,0) * (*this)(1,2))),
                inv_det * ((*this)(0,0) * (*this)(2,2) - (*this)(2,0) * (*this)(0,2)),
                inv_det * (-((*this)(0,0) * (*this)(1,2) - (*this)(1,0) * (*this)(0,2))),

                inv_det * ((*this)(1,0) * (*this)(2,1) - (*this)(2,0) * (*this)(1,1)),
                inv_det * (-((*this)(0,0) * (*this)(2,1) - (*this)(2,0) * (*this)(0,1))),
                inv_det * ((*this)(0,0) * (*this)(1,1) - (*this)(1,0) * (*this)(0,1))
            };

            return inverse;
        }

    };

    typedef Mat3<int> Mat3i;
    typedef Mat3<float> Mat3f;
    typedef Mat3<double> Mat3d;

    template<typename T>
    Mat3<T> operator*(const T& scalar, const Mat3<T>& m) {
        return m * scalar;
    }
}

#endif