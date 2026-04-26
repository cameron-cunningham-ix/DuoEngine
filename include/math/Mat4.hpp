#ifndef MAT3_HPP
#define MAT3_HPP

#include <cmath>
#include <cassert>
#include <array>
#include <utility>
#include <stdexcept>

#include "Vec4.hpp"

namespace RendMath{
    template<typename T>
    class Mat4 {
    public:
        // Identity constructor
        Mat4() {
            m = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
        }
        // 16 value constructor; parameters are in row-major order, and get stored as column-major order
        Mat4(T a, T b, T c, T d, T e, T f, T g, T h, T i, T j, T k, T l, T m, T n, T o, T p) {
            this->m = { a, e, i, m, b, f, j, n, c, g, k, o, d, h, l, p};
        }
        // Column-major layout
        std::array<T, 16> m;

        T& operator()(int row, int col) {
            return m[col * 4 + row];
        }
        
        T operator()(int row, int col) const {
            return m[col * 4 + row];
        }

        static Mat4<T> identity() {
            return Mat4<T>(T(1), T(0), T(0), T(0),
                            T(0), T(1), T(0), T(0),
                            T(0), T(0), T(1), T(0),
                            T(0), T(0), T(0), T(1));
        }

        // Matrix multiplication
        Mat4<T> operator*(const Mat4<T>& a) const {
            Mat4<T> result;

            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    result(j, i) = (*this)(j, 0) * a(0, i) +
                                   (*this)(j, 1) * a(1, i) +
                                   (*this)(j, 2) * a(2, i) +
                                   (*this)(j, 3) * a(3, i);
                }
            }
            return result;
        }
        
        // Scalar multiplication
        Mat4<T> operator*(const T& scalar) const {
            Mat4<T> result;

            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    result(j, i) = (*this)(j, i) * scalar;
                }
            }
            return result;
        }
        
        Mat4<T>& operator*=(const T& scalar) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    (*this)(j, i) *= scalar;
                }
            }
            return *this;
        }

        // Vector multiplication
        Vec4<T> operator*(const Vec4<T>& v) const {
            Vec4<T> result;
            for (int i = 0; i < 4; i++) {
                result[i] = v[0] * (*this)(i, 0) +
                            v[1] * (*this)(i, 1) +
                            v[2] * (*this)(i, 2) +
                            v[3] * (*this)(i, 3);
            }
            return result;
        }

        bool operator==(const Mat4<T>& a) const {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (a(j,i) != (*this)(j,i)) return false;
                }
            }
            return true;
        }

        Mat4<T> transpose() const {
            Mat4<T> result;

            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    result(j, i) = (*this)(i, j);
                }
            }
            return result;
        }

        Mat4<T>& transposeInPlace() {
            std::swap((*this)(1,0), (*this)(0,1));
            std::swap((*this)(2,0), (*this)(0,2));
            std::swap((*this)(3,0), (*this)(0,3));
            
            std::swap((*this)(1,2), (*this)(2,1));
            std::swap((*this)(1,3), (*this)(3,1));
            std::swap((*this)(2,3), (*this)(3,2));

            return *this;
        }

        T determinant() const {
            T result = T(0);

            result += (*this)(0,0) * ((*this)(1,1) * ((*this)(2,2)*(*this)(3,3) - (*this)(2,3)*(*this)(3,2)) -
                                     (*this)(1,2) * ((*this)(2,1)*(*this)(3,3) - (*this)(2,3)*(*this)(3,1)) +
                                     (*this)(1,3) * ((*this)(2,1)*(*this)(3,2) - (*this)(2,2)*(*this)(3,1)));

            result -= (*this)(1,0) * ((*this)(0,1) * ((*this)(2,2)*(*this)(3,3) - (*this)(2,3)*(*this)(3,2)) -
                                     (*this)(0,2) * ((*this)(2,1)*(*this)(3,3) - (*this)(2,3)*(*this)(3,1)) +
                                     (*this)(0,3) * ((*this)(2,1)*(*this)(3,2) - (*this)(2,2)*(*this)(3,1)));

            result += (*this)(2,0) * ((*this)(0,1) * ((*this)(1,2)*(*this)(3,3) - (*this)(1,3)*(*this)(3,2)) -
                                     (*this)(0,2) * ((*this)(1,1)*(*this)(3,3) - (*this)(1,3)*(*this)(3,1)) +
                                     (*this)(0,3) * ((*this)(1,1)*(*this)(3,2) - (*this)(1,2)*(*this)(3,1)));
            
            result -= (*this)(3,0) * ((*this)(0,1) * ((*this)(1,2)*(*this)(2,3) - (*this)(1,3)*(*this)(2,2)) -
                                     (*this)(0,2) * ((*this)(1,1)*(*this)(2,3) - (*this)(1,3)*(*this)(2,1)) +
                                     (*this)(0,3) * ((*this)(1,1)*(*this)(2,2) - (*this)(1,2)*(*this)(2,1)));
            return result;
        }

        //  m(0,0)  m(0,1)  m(0,2)  m(0,3)
        //  m(1,0)  m(1,1)  m(1,2)  m(1,3)
        //  m(2,0)  m(2,1)  m(2,2)  m(2,3)
        //  m(3,0)  m(3,1)  m(3,2)  m(3,3)

        /// @brief 
        /// @param row 
        /// @param col
        /// @return 
        T calculate3x3det(int row, int col) const {
            switch(col*4 + row) {
                case 0:
                    return (*this)(1,1) * ((*this)(2,2)*(*this)(3,3) - (*this)(2,3)*(*this)(3,2)) -
                            (*this)(1,2) * ((*this)(2,1)*(*this)(3,3) - (*this)(2,3)*(*this)(3,1)) +
                            (*this)(1,3) * ((*this)(2,1)*(*this)(3,2) - (*this)(2,2)*(*this)(3,1));
                case 1:
                    return (*this)(0,1) * ((*this)(2,2)*(*this)(3,3) - (*this)(2,3)*(*this)(3,2)) -
                            (*this)(0,2) * ((*this)(2,1)*(*this)(3,3) - (*this)(2,3)*(*this)(3,1)) +
                            (*this)(0,3) * ((*this)(2,1)*(*this)(3,2) - (*this)(2,2)*(*this)(3,1));
                case 2:
                    return (*this)(0,1) * ((*this)(1,2)*(*this)(3,3) - (*this)(1,3)*(*this)(3,2)) -
                            (*this)(0,2) * ((*this)(1,1)*(*this)(3,3) - (*this)(1,3)*(*this)(3,1)) +
                            (*this)(0,3) * ((*this)(1,1)*(*this)(3,2) - (*this)(1,2)*(*this)(3,1));
                case 3:
                    return (*this)(0,1) * ((*this)(1,2)*(*this)(2,3) - (*this)(1,3)*(*this)(2,2)) -
                            (*this)(0,2) * ((*this)(1,1)*(*this)(2,3) - (*this)(1,3)*(*this)(2,1)) +
                            (*this)(0,3) * ((*this)(1,1)*(*this)(2,2) - (*this)(1,2)*(*this)(2,1));
                case 4:
                    return (*this)(1,0) * ((*this)(2,2)*(*this)(3,3) - (*this)(2,3)*(*this)(3,2)) -
                            (*this)(1,2) * ((*this)(2,0)*(*this)(3,3) - (*this)(2,3)*(*this)(3,0)) +
                            (*this)(1,3) * ((*this)(2,0)*(*this)(3,2) - (*this)(2,2)*(*this)(3,0));
                case 5:
                    return (*this)(0,0) * ((*this)(2,2)*(*this)(3,3) - (*this)(2,3)*(*this)(3,2)) -
                            (*this)(0,2) * ((*this)(2,0)*(*this)(3,3) - (*this)(2,3)*(*this)(3,0)) +
                            (*this)(0,3) * ((*this)(2,0)*(*this)(3,2) - (*this)(2,2)*(*this)(3,0));
                case 6:
                    return (*this)(0,0) * ((*this)(1,2)*(*this)(3,3) - (*this)(1,3)*(*this)(3,2)) -
                            (*this)(0,2) * ((*this)(1,0)*(*this)(3,3) - (*this)(1,3)*(*this)(3,0)) +
                            (*this)(0,3) * ((*this)(1,0)*(*this)(3,2) - (*this)(1,2)*(*this)(3,0));
                case 7:
                    return (*this)(0,0) * ((*this)(1,2)*(*this)(2,3) - (*this)(1,3)*(*this)(2,2)) -
                            (*this)(0,2) * ((*this)(1,0)*(*this)(2,3) - (*this)(1,3)*(*this)(2,0)) +
                            (*this)(0,3) * ((*this)(1,0)*(*this)(2,2) - (*this)(1,2)*(*this)(2,0));
                case 8:
                    return (*this)(1,0) * ((*this)(2,1)*(*this)(3,3) - (*this)(2,3)*(*this)(3,1)) -
                            (*this)(1,1) * ((*this)(2,0)*(*this)(3,3) - (*this)(2,3)*(*this)(3,0)) +
                            (*this)(1,3) * ((*this)(2,0)*(*this)(3,1) - (*this)(2,1)*(*this)(3,0));
                case 9:
                    return (*this)(0,0) * ((*this)(2,1)*(*this)(3,3) - (*this)(2,3)*(*this)(3,1)) -
                            (*this)(0,1) * ((*this)(2,0)*(*this)(3,3) - (*this)(2,3)*(*this)(3,0)) +
                            (*this)(0,3) * ((*this)(2,0)*(*this)(3,1) - (*this)(2,1)*(*this)(3,0));
                case 10:
                    return (*this)(0,0) * ((*this)(1,1)*(*this)(3,3) - (*this)(1,3)*(*this)(3,1)) -
                            (*this)(0,1) * ((*this)(1,0)*(*this)(3,3) - (*this)(1,3)*(*this)(3,0)) +
                            (*this)(0,3) * ((*this)(1,0)*(*this)(3,1) - (*this)(1,1)*(*this)(3,0));
                case 11:
                    return (*this)(0,0) * ((*this)(1,1)*(*this)(2,3) - (*this)(1,3)*(*this)(2,1)) -
                            (*this)(0,1) * ((*this)(1,0)*(*this)(2,3) - (*this)(1,3)*(*this)(2,0)) +
                            (*this)(0,3) * ((*this)(1,0)*(*this)(2,1) - (*this)(1,1)*(*this)(2,0));
                case 12:
                    return (*this)(1,0) * ((*this)(2,1)*(*this)(3,2) - (*this)(2,2)*(*this)(3,1)) -
                            (*this)(1,1) * ((*this)(2,0)*(*this)(3,2) - (*this)(2,2)*(*this)(3,0)) +
                            (*this)(1,2) * ((*this)(2,0)*(*this)(3,1) - (*this)(2,1)*(*this)(3,0));
                case 13:
                    return (*this)(0,0) * ((*this)(2,1)*(*this)(3,2) - (*this)(2,2)*(*this)(3,1)) -
                            (*this)(0,1) * ((*this)(2,0)*(*this)(3,2) - (*this)(2,2)*(*this)(3,0)) +
                            (*this)(0,2) * ((*this)(2,0)*(*this)(3,1) - (*this)(2,1)*(*this)(3,0));
                case 14:
                    return (*this)(0,0) * ((*this)(1,1)*(*this)(3,2) - (*this)(1,2)*(*this)(3,1)) -
                            (*this)(0,1) * ((*this)(1,0)*(*this)(3,2) - (*this)(1,2)*(*this)(3,0)) +
                            (*this)(0,2) * ((*this)(1,0)*(*this)(3,1) - (*this)(1,1)*(*this)(3,0));
                case 15:
                    return (*this)(0,0) * ((*this)(1,1)*(*this)(2,2) - (*this)(1,2)*(*this)(2,1)) -
                            (*this)(0,1) * ((*this)(1,0)*(*this)(2,2) - (*this)(1,2)*(*this)(2,0)) +
                            (*this)(0,2) * ((*this)(1,0)*(*this)(2,1) - (*this)(1,1)*(*this)(2,0));
                default:
                    return T(0);

            }
            
        }

        

        Mat4<T> inverse() const {
            T det = determinant();
            if (det == T(0)) throw std::runtime_error("non-invertible matrix");
            T inv_det = T(1) / det;

            Mat4<T> inverse = {
                inv_det * calculate3x3det(0,0),
                inv_det * -calculate3x3det(1,0),
                inv_det * calculate3x3det(2,0),
                inv_det * -calculate3x3det(3,0),

                inv_det * -calculate3x3det(0,1),
                inv_det * calculate3x3det(1,1),
                inv_det * -calculate3x3det(2,1),
                inv_det * calculate3x3det(3,1),

                inv_det * calculate3x3det(0,2),
                inv_det * -calculate3x3det(1,2),
                inv_det * calculate3x3det(2,2),
                inv_det * -calculate3x3det(3,2),

                inv_det * -calculate3x3det(0,3),
                inv_det * calculate3x3det(1,3),
                inv_det * -calculate3x3det(2,3),
                inv_det * calculate3x3det(3,3),
            };
            return inverse;
        }

        static Mat4<T> translate(Mat4<T> matrix, Vec3<T> vector) {
            return matrix * Mat4<T>(T(1), T(0), T(0), T(0),
                                    T(0), T(1), T(0), T(0),
                                    T(0), T(0), T(1), T(0),
                                    T(vector.x), T(vector.y), T(vector.z), T(1));
        }

    };

    typedef Mat4<int> Mat4i;
    typedef Mat4<float> Mat4f;
    typedef Mat4<double> Mat4d;

    template<typename T>
    Mat4<T> operator*(const T& scalar, const Mat4<T>& m) {
        return m * scalar;
    }
}

#endif