#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Vector.h"

struct Matrix2x2
{
    union {
        fp_type a[2][2];
        struct {
            fp_type f00, f01;
            fp_type f10, f11;
        } d;
    } vals;

    Matrix2x2 inverse() const;                              // Compute the matrix inverse
    Matrix2x2 transpose() const;                            // Transpose rows and columns

    Matrix2x2 operator+(const Matrix2x2& other) const;      // Adds two Matrix2x2's together (component-wise)
    void operator+=(const Matrix2x2& other);			    // Adds two Matrix2x2's together (component-wise)
    Matrix2x2 operator-(const Matrix2x2& other) const;      // Subtracts a Matrix2x2 from another Matrix2x2 (component-wise)
    void operator-=(const Matrix2x2& other);			    // Subtracts a Matrix2x2 from another Matrix2x2 (component-wise)
    Matrix2x2 operator*(fp_type scalar) const;		        // Scalar multiply
    void operator*=(fp_type scalar);				        // Scalar multiply
    Matrix2x2 operator/(fp_type scalar) const;		        // Scalar divide
    void operator/=(fp_type scalar);				        // Scalar divide

    Vector2d operator*(const Vector2d& other) const;       // Apply the matrix transform to a Vector3d

    Matrix2x2 operator-() const;
};

struct Matrix3x3
{
    union {
        fp_type a[3][3];
        struct {
            fp_type f00, f01, f02;
            fp_type f10, f11, f12;
            fp_type f20, f21, f22;
        } d;
    } vals;

    Matrix3x3 inverse() const;                              // Compute the matrix inverse
    Matrix3x3 transpose() const;                            // Transpose rows and columns

    Matrix3x3 operator+(const Matrix3x3& other) const;      // Adds two Matrix3x3's together (component-wise)
    void operator+=(const Matrix3x3& other);			    // Adds two Matrix3x3's together (component-wise)
    Matrix3x3 operator-(const Matrix3x3& other) const;      // Subtracts a Matrix3x3 from another Matrix3x3 (component-wise)
    void operator-=(const Matrix3x3& other);			    // Subtracts a Matrix3x3 from another Matrix3x3 (component-wise)
    Matrix3x3 operator*(fp_type scalar) const;		        // Scalar multiply
    void operator*=(fp_type scalar);				        // Scalar multiply
    Matrix3x3 operator/(fp_type scalar) const;		        // Scalar divide
    void operator/=(fp_type scalar);				        // Scalar divide

    Vector3d operator*(const Vector3d& other) const;       // Apply the matrix transform to a Vector3d

    Matrix3x3 operator-() const;
};

struct Matrix4x4
{
    union {
        fp_type a[4][4];
        struct {
            fp_type f00, f01, f02, f03;
            fp_type f10, f11, f12, f13;
            fp_type f20, f21, f22, f23;
            fp_type f30, f31, f32, f33;
        } d;
    } vals;

    Matrix4x4 inverse() const;                              // Compute the matrix inverse
    Matrix4x4 transpose() const;                            // Transpose rows and columns

    Matrix4x4 operator+(const Matrix4x4& other) const;      // Adds two Matrix4x4's together (component-wise)
    void operator+=(const Matrix4x4& other);			    // Adds two Matrix4x4's together (component-wise)
    Matrix4x4 operator-(const Matrix4x4& other) const;      // Subtracts a Matrix4x4 from another Matrix4x4 (component-wise)
    void operator-=(const Matrix4x4& other);			    // Subtracts a Matrix4x4 from another Matrix4x4 (component-wise)
    Matrix4x4 operator*(fp_type scalar) const;		        // Scalar multiply
    void operator*=(fp_type scalar);				        // Scalar multiply
    Matrix4x4 operator/(fp_type scalar) const;		        // Scalar divide
    void operator/=(fp_type scalar);				        // Scalar divide

    fp_type det() const;

    Vector3d operator*(const Vector3d& other) const;       // Apply the matrix transform to a Vector3d

    Matrix4x4 operator-() const;
};

#endif // _MATRIX_H_
