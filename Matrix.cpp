#include "Matrix.h"

Matrix4x4 Matrix4x4::inverse() const
{
    fp_type res = det();
    if(res == 0)
        return Matrix4x4::zero;
    return transpose()/det();
}

fp_type Matrix4x4::det() const
{
    fp_type ret = 0;

    ret += (a11*a22*a33*a44 + a11*a23*a34*a42 + a11*a24*a32*a43);
    ret += (a12*a21*a34*a43 + a12*a23*a31*a44 + a12*a24*a33*a41);
    ret += (a13*a21*a32*a44 + a13*a22*a34*a41 + a13*a24*a31*a42);
    ret += (a14*a21*a33*a42 + a14*a22*a31*a43 + a14*a23*a32*a41);

    ret -= (a11*a22*a34*a43 + a11*a23*a32*a44 + a11*a24*a33*a42);
    ret -= (a12*a21*a33*a44 + a12*a23*a34*a41 + a12*a24*a31*a43);
    ret -= (a13*a21*a34*a42 + a13*a22*a31*a44 + a13*a24*a32*a41);
    ret -= (a14*a21*a32*a43 + a14*a22*a33*a41 + a14*a23*a31*a42);

    return ret;
}

Matrix4x4 Matrix4x4::transpose() const
{
    Matrix4x4 ret;
    ret.vals.d.f00 = vals.d.f00;
    ret.vals.d.f11 = vals.d.f11;
    ret.vals.d.f22 = vals.d.f22;
    ret.vals.d.f33 = vals.d.f33;

    ret.vals.d.f01 = vals.d.f10;
    ret.vals.d.f02 = vals.d.f20;
    ret.vals.d.f03 = vals.d.f30;

    ret.vals.d.f10 = vals.d.f01;
    ret.vals.d.f12 = vals.d.f21;
    ret.vals.d.f13 = vals.d.f31;

    ret.vals.d.f20 = vals.d.f02;
    ret.vals.d.f21 = vals.d.f12;
    ret.vals.d.f23 = vals.d.f32;

    ret.vals.d.f30 = vals.d.f03;
    ret.vals.d.f31 = vals.d.f13;
    ret.vals.d.f32 = vals.d.f23;

    return ret;
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const
{
    Matrix4x4 ret;

    for(uint32_t i = 0; i < 4; i++)
    {
        for(uint32_t j = 0; j < 4; j++)
        {
            ret.vals.a[i][j] = vals.a[i][j] + other.vals.a[i][j];
        }
    }

    return ret;
}

void Matrix4x4::operator+=(const Matrix4x4& other)
{
    for(uint32_t i = 0; i < 4; i++)
    {
        for(uint32_t j = 0; j < 4; j++)
        {
            vals.a[i][j] += other.vals.a[i][j];
        }
    }
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other) const
{
    Matrix4x4 ret;

    for(uint32_t i = 0; i < 4; i++)
    {
        for(uint32_t j = 0; j < 4; j++)
        {
            ret.vals.a[i][j] = vals.a[i][j] - other.vals.a[i][j];
        }
    }

    return ret;
}

void Matrix4x4::operator-=(const Matrix4x4& other)
{
    for(uint32_t i = 0; i < 4; i++)
    {
        for(uint32_t j = 0; j < 4; j++)
        {
            vals.a[i][j] -= other.vals.a[i][j];
        }
    }
}

// NO BUENO. Use Python to generate stuff like this, otherwise your sanity will be tested.
Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const
{
    Matrix4x4 ret;

    ret.vals.d.f00 = (vals.d.f00 * other.vals.d.f00) + (vals.d.f01 * other.vals.d.f10) + (vals.d.f02 * other.vals.d.f20) + (vals.d.f03 * other.vals.d.f30);
    ret.vals.d.f01 = (vals.d.f00 * other.vals.d.f01) + (vals.d.f01 * other.vals.d.f11) + (vals.d.f02 * other.vals.d.f21) + (vals.d.f03 * other.vals.d.f31);
    ret.vals.d.f02 = (vals.d.f00 * other.vals.d.f02) + (vals.d.f01 * other.vals.d.f12) + (vals.d.f02 * other.vals.d.f22) + (vals.d.f03 * other.vals.d.f32);
    ret.vals.d.f03 = (vals.d.f00 * other.vals.d.f03) + (vals.d.f01 * other.vals.d.f13) + (vals.d.f02 * other.vals.d.f23) + (vals.d.f03 * other.vals.d.f33);
    ret.vals.d.f10 = (vals.d.f10 * other.vals.d.f00) + (vals.d.f11 * other.vals.d.f10) + (vals.d.f12 * other.vals.d.f20) + (vals.d.f13 * other.vals.d.f30);
    ret.vals.d.f11 = (vals.d.f10 * other.vals.d.f01) + (vals.d.f11 * other.vals.d.f11) + (vals.d.f12 * other.vals.d.f21) + (vals.d.f13 * other.vals.d.f31);
    ret.vals.d.f12 = (vals.d.f10 * other.vals.d.f02) + (vals.d.f11 * other.vals.d.f12) + (vals.d.f12 * other.vals.d.f22) + (vals.d.f13 * other.vals.d.f32);
    ret.vals.d.f13 = (vals.d.f10 * other.vals.d.f03) + (vals.d.f11 * other.vals.d.f13) + (vals.d.f12 * other.vals.d.f23) + (vals.d.f13 * other.vals.d.f33);
    ret.vals.d.f20 = (vals.d.f20 * other.vals.d.f00) + (vals.d.f21 * other.vals.d.f10) + (vals.d.f22 * other.vals.d.f20) + (vals.d.f23 * other.vals.d.f30);
    ret.vals.d.f21 = (vals.d.f20 * other.vals.d.f01) + (vals.d.f21 * other.vals.d.f11) + (vals.d.f22 * other.vals.d.f21) + (vals.d.f23 * other.vals.d.f31);
    ret.vals.d.f22 = (vals.d.f20 * other.vals.d.f02) + (vals.d.f21 * other.vals.d.f12) + (vals.d.f22 * other.vals.d.f22) + (vals.d.f23 * other.vals.d.f32);
    ret.vals.d.f23 = (vals.d.f20 * other.vals.d.f03) + (vals.d.f21 * other.vals.d.f13) + (vals.d.f22 * other.vals.d.f23) + (vals.d.f23 * other.vals.d.f33);
    ret.vals.d.f30 = (vals.d.f30 * other.vals.d.f00) + (vals.d.f31 * other.vals.d.f10) + (vals.d.f32 * other.vals.d.f20) + (vals.d.f33 * other.vals.d.f30);
    ret.vals.d.f31 = (vals.d.f30 * other.vals.d.f01) + (vals.d.f31 * other.vals.d.f11) + (vals.d.f32 * other.vals.d.f21) + (vals.d.f33 * other.vals.d.f31);
    ret.vals.d.f32 = (vals.d.f30 * other.vals.d.f02) + (vals.d.f31 * other.vals.d.f12) + (vals.d.f32 * other.vals.d.f22) + (vals.d.f33 * other.vals.d.f32);
    ret.vals.d.f33 = (vals.d.f30 * other.vals.d.f03) + (vals.d.f31 * other.vals.d.f13) + (vals.d.f32 * other.vals.d.f23) + (vals.d.f33 * other.vals.d.f33);

    return ret;
}

void Matrix4x4::operator*=(const Matrix4x4& other)
{
    Matrix4x4 res = (*this) * other;
    memcpy(vals.a, res.vals.a, 16 * sizeof(fp_type));
}

Matrix4x4 Matrix4x4::operator/(const Matrix4x4& other) const
{
    return (*this) * other.inverse();
}

void Matrix4x4::operator/=(const Matrix4x4& other)
{
    Matrix4x4 res = (*this) / other;
    memcpy(vals.a, res.vals.a, 16 * sizeof(fp_type));
}


Matrix4x4 Matrix4x4::operator*(fp_type scalar) const
{
    Matrix4x4 ret;

    for(uint32_t i = 0; i < 16; i++)
        ret.vals.a[i] = vals.a[i] * scalar;

    return ret;
}

void Matrix4x4::operator*=(fp_type scalar)
{
    Matrix4x4 res = (*this) * scalar;
    memcpy(vals.a, res.vals.a, 16 * sizeof(fp_type));
}

Matrix4x4 Matrix4x4::operator/(fp_type scalar) const
{
    Matrix4x4 ret;

    for(uint32_t i = 0; i < 16; i++)
        ret.vals.a[i] = vals.a[i] / scalar;

    return ret;
}

void Matrix4x4::operator/=(fp_type scalar)
{
    Matrix4x4 res = (*this) / scalar;
    memcpy(vals.a, res.vals.a, 16 * sizeof(fp_type));
}

Vector3d Matrix4x4::operator*(const Vector3d& other) const
{
    Vector3d ret;

    ret.x = (vals.d.f00 * other.x) + (vals.d.f01 * other.y) + (vals.d.f02 * other.z) + (vals.d.f03);
    ret.y = (vals.d.f10 * other.x) + (vals.d.f11 * other.y) + (vals.d.f12 * other.z) + (vals.d.f13);
    ret.z = (vals.d.f20 * other.x) + (vals.d.f21 * other.y) + (vals.d.f22 * other.z) + (vals.d.f23);

    return ret;
}

Matrix4x4 Matrix4x4::operator-() const
{
    Matrix4x4 ret;

    for(uint32_t i = 0; i < 16; i++)
        ret.vals.a[i] = -vals.a[i];

    return ret;
}

