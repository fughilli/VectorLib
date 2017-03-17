#ifndef _MATRIX_H_
#define _MATRIX_H_

#ifdef __cplusplus

#include "Vector.h"

struct Matrix2x2
{
    union
    {
        fp_type a[2][2];
        struct
        {
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
    union
    {
        fp_type a[3][3];
        struct
        {
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
    union
    {
        fp_type a[4][4];
        struct
        {
            fp_type f00, f01, f02, f03;
            fp_type f10, f11, f12, f13;
            fp_type f20, f21, f22, f23;
            fp_type f30, f31, f32, f33;
        } d;
    } vals;

    Matrix4x4(const fp_type* init);
    Matrix4x4(fp_type f00, fp_type f01, fp_type f02, fp_type f03,
              fp_type f10, fp_type f11, fp_type f12, fp_type f13,
              fp_type f20, fp_type f21, fp_type f22, fp_type f23,
              fp_type f30, fp_type f31, fp_type f32, fp_type f33);
    Matrix4x4();

    Matrix4x4(const Quaternion& rot);
    Matrix4x4(fp_type scale);
    Matrix4x4(const Vector3d& trans);

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

    Matrix4x4 operator*(const Matrix4x4& other) const;		// Scalar multiply
    void operator*=(const Matrix4x4& other);				// Scalar multiply
    Matrix4x4 operator/(const Matrix4x4& other) const;		// Scalar divide
    void operator/=(const Matrix4x4& other);				// Scalar divide

    fp_type det() const;

    Vector3d operator*(const Vector3d& other) const;       // Apply the matrix transform to a Vector3d
    Vector3d translation() const;

    Matrix4x4 operator-() const;

    static const Matrix4x4 zero;
    static const Matrix4x4 identity;
    static const Matrix4x4 one;
};

#if defined(ARDUINO) || defined(ENERGIA)

#else
std::ostream& operator<<(std::ostream& os, const Matrix4x4& vec);
#endif

#endif

#endif // _MATRIX_H_
