#include "Matrix.h"

Matrix4x4 Matrix4x4::inverse() const
{

}

Matrix4x4 Matrix4x4::det() const
{

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

Matrix4x4 Matrix4x4::operator*(fp_type scalar) const
{

}

void Matrix4x4::operator*=(fp_type scalar)
{

}

Matrix4x4 Matrix4x4::operator/(fp_type scalar) const
{

}

void Matrix4x4::operator/=(fp_type scalar)
{

}

Vector3d Matrix4x4::operator*(const Vector3d& other) const
{

}

Matrix4x4 Matrix4x4::operator-() const
{

}

