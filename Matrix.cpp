#ifdef __cplusplus

#include "Matrix.h"
#include <cstring>

#define _FP(x) ((fp_type)(x))

const Matrix4x4 Matrix4x4::zero = Matrix4x4();
const Matrix4x4 Matrix4x4::one = Matrix4x4(1,1,1,1,
                                 1,1,1,1,
                                 1,1,1,1,
                                 1,1,1,1);
const Matrix4x4 Matrix4x4::identity = Matrix4x4(1,0,0,0,
                                      0,1,0,0,
                                      0,0,1,0,
                                      0,0,0,1);

static void zeroInit(void* a, uint32_t sz)
{
    for(uint32_t i = 0; i < sz; i++)
    {
        ((fp_type*)a)[i] = (fp_type)0;
    }
}

Matrix4x4::Matrix4x4()
{
    zeroInit(vals.a, 16);
}

Matrix4x4::Matrix4x4(const fp_type* init)
{
    for(uint32_t i = 0; i < 16; i++)
    {
        ((fp_type*)vals.a)[i] = init[i];
    }
}

Matrix4x4::Matrix4x4(fp_type f00, fp_type f01, fp_type f02, fp_type f03,
                     fp_type f10, fp_type f11, fp_type f12, fp_type f13,
                     fp_type f20, fp_type f21, fp_type f22, fp_type f23,
                     fp_type f30, fp_type f31, fp_type f32, fp_type f33)
{
    vals.d.f00 = f00;
    vals.d.f01 = f01;
    vals.d.f02 = f02;
    vals.d.f03 = f03;

    vals.d.f10 = f10;
    vals.d.f11 = f11;
    vals.d.f12 = f12;
    vals.d.f13 = f13;

    vals.d.f20 = f20;
    vals.d.f21 = f21;
    vals.d.f22 = f22;
    vals.d.f23 = f23;

    vals.d.f30 = f30;
    vals.d.f31 = f31;
    vals.d.f32 = f32;
    vals.d.f33 = f33;
}

Matrix4x4::Matrix4x4(const Quaternion& rot)
{
    fp_type xx = rot.x*rot.x;
    fp_type xy = rot.x*rot.y;
    fp_type xz = rot.x*rot.z;
    fp_type xw = rot.x*rot.w;

    fp_type yy = rot.y*rot.y;
    fp_type yz = rot.y*rot.z;
    fp_type yw = rot.y*rot.w;

    fp_type zz = rot.z*rot.z;
    fp_type zw = rot.z*rot.w;

    vals.d.f00 = _FP(1) - (_FP(2)*yy) - (_FP(2)*zz);
    vals.d.f10 = _FP(2)*(xy + zw);
    vals.d.f20 = _FP(2)*(xz - yw);
    vals.d.f30 = 0;

    vals.d.f01 = _FP(2)*(xy - zw);
    vals.d.f11 = _FP(1) - (_FP(2)*xx) - (_FP(2)*zz);
    vals.d.f21 = _FP(2)*(yz + xw);
    vals.d.f31 = 0;

    vals.d.f02 = _FP(2)*(xz + yw);
    vals.d.f12 = _FP(2)*(yz - xw);
    vals.d.f22 = _FP(1) - (_FP(2)*xx) - (_FP(2)*yy);
    vals.d.f32 = 0;

    vals.d.f03 = 0;
    vals.d.f13 = 0;
    vals.d.f23 = 0;
    vals.d.f33 = 1;
}

Matrix4x4::Matrix4x4(fp_type scale)
{
    zeroInit(vals.a, 16);
    vals.d.f00 = scale;
    vals.d.f11 = scale;
    vals.d.f22 = scale;
    vals.d.f33 = 1;
}

Matrix4x4::Matrix4x4(const Vector3d& trans)
{
    zeroInit(vals.a, 16);
    vals.d.f03 = trans.x;
    vals.d.f13 = trans.y;
    vals.d.f23 = trans.z;

    vals.d.f00 = 1;
    vals.d.f11 = 1;
    vals.d.f22 = 1;
    vals.d.f33 = 1;
}

Matrix4x4 Matrix4x4::inverse() const
{
    fp_type res = det();
    if(res == 0)
        return Matrix4x4::zero;
    return transpose()/det();
}

// Credit: http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html
fp_type Matrix4x4::det() const
{
    fp_type ret = 0;

//    ret += (vals.d.f11*vals.d.f22*vals.d.f33*vals.d.f44 + vals.d.f11*vals.d.f23*vals.d.f34*vals.d.f42 + vals.d.f11*vals.d.f24*vals.d.f32*vals.d.f43);
//    ret += (vals.d.f12*vals.d.f21*vals.d.f34*vals.d.f43 + vals.d.f12*vals.d.f23*vals.d.f31*vals.d.f44 + vals.d.f12*vals.d.f24*vals.d.f33*vals.d.f41);
//    ret += (vals.d.f13*vals.d.f21*vals.d.f32*vals.d.f44 + vals.d.f13*vals.d.f22*vals.d.f34*vals.d.f41 + vals.d.f13*vals.d.f24*vals.d.f31*vals.d.f42);
//    ret += (vals.d.f14*vals.d.f21*vals.d.f33*vals.d.f42 + vals.d.f14*vals.d.f22*vals.d.f31*vals.d.f43 + vals.d.f14*vals.d.f23*vals.d.f32*vals.d.f41);
//
//    ret -= (vals.d.f11*vals.d.f22*vals.d.f34*vals.d.f43 + vals.d.f11*vals.d.f23*vals.d.f32*vals.d.f44 + vals.d.f11*vals.d.f24*vals.d.f33*vals.d.f42);
//    ret -= (vals.d.f12*vals.d.f21*vals.d.f33*vals.d.f44 + vals.d.f12*vals.d.f23*vals.d.f34*vals.d.f41 + vals.d.f12*vals.d.f24*vals.d.f31*vals.d.f43);
//    ret -= (vals.d.f13*vals.d.f21*vals.d.f34*vals.d.f42 + vals.d.f13*vals.d.f22*vals.d.f31*vals.d.f44 + vals.d.f13*vals.d.f24*vals.d.f32*vals.d.f41);
//    ret -= (vals.d.f14*vals.d.f21*vals.d.f32*vals.d.f43 + vals.d.f14*vals.d.f22*vals.d.f33*vals.d.f41 + vals.d.f14*vals.d.f23*vals.d.f31*vals.d.f42);

    ret += (vals.d.f00*vals.d.f11*vals.d.f22*vals.d.f33 + vals.d.f00*vals.d.f12*vals.d.f23*vals.d.f31 + vals.d.f00*vals.d.f13*vals.d.f21*vals.d.f32);
    ret += (vals.d.f01*vals.d.f10*vals.d.f23*vals.d.f32 + vals.d.f01*vals.d.f12*vals.d.f20*vals.d.f33 + vals.d.f01*vals.d.f13*vals.d.f22*vals.d.f30);
    ret += (vals.d.f02*vals.d.f10*vals.d.f21*vals.d.f33 + vals.d.f02*vals.d.f11*vals.d.f23*vals.d.f30 + vals.d.f02*vals.d.f13*vals.d.f20*vals.d.f31);
    ret += (vals.d.f03*vals.d.f10*vals.d.f22*vals.d.f31 + vals.d.f03*vals.d.f11*vals.d.f20*vals.d.f32 + vals.d.f03*vals.d.f12*vals.d.f21*vals.d.f30);

    ret -= (vals.d.f00*vals.d.f11*vals.d.f23*vals.d.f32 + vals.d.f00*vals.d.f12*vals.d.f21*vals.d.f33 + vals.d.f00*vals.d.f13*vals.d.f22*vals.d.f31);
    ret -= (vals.d.f01*vals.d.f10*vals.d.f22*vals.d.f33 + vals.d.f01*vals.d.f12*vals.d.f23*vals.d.f30 + vals.d.f01*vals.d.f13*vals.d.f20*vals.d.f32);
    ret -= (vals.d.f02*vals.d.f10*vals.d.f23*vals.d.f31 + vals.d.f02*vals.d.f11*vals.d.f20*vals.d.f33 + vals.d.f02*vals.d.f13*vals.d.f21*vals.d.f30);
    ret -= (vals.d.f03*vals.d.f10*vals.d.f21*vals.d.f32 + vals.d.f03*vals.d.f11*vals.d.f22*vals.d.f30 + vals.d.f03*vals.d.f12*vals.d.f20*vals.d.f31);

    return ret;
}

Matrix4x4 Matrix4x4::transpose() const
{
    Matrix4x4 ret;

    ret.vals.d.f00 = vals.d.f00;
    ret.vals.d.f01 = vals.d.f10;
    ret.vals.d.f02 = vals.d.f20;
    ret.vals.d.f03 = vals.d.f30;

    ret.vals.d.f10 = vals.d.f01;
    ret.vals.d.f11 = vals.d.f11;
    ret.vals.d.f12 = vals.d.f21;
    ret.vals.d.f13 = vals.d.f31;

    ret.vals.d.f20 = vals.d.f02;
    ret.vals.d.f21 = vals.d.f12;
    ret.vals.d.f22 = vals.d.f22;
    ret.vals.d.f23 = vals.d.f32;

    ret.vals.d.f30 = vals.d.f03;
    ret.vals.d.f31 = vals.d.f13;
    ret.vals.d.f32 = vals.d.f23;
    ret.vals.d.f33 = vals.d.f33;

    return ret;
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const
{
    Matrix4x4 ret;

    for(uint32_t i = 0; i < 16; i++)
    {
        ((fp_type*)ret.vals.a)[i] = ((fp_type*)vals.a)[i] + ((fp_type*)other.vals.a)[i];
    }

    return ret;
}

void Matrix4x4::operator+=(const Matrix4x4& other)
{
    for(uint32_t i = 0; i < 16; i++)
    {
        ((fp_type*)vals.a)[i] += ((fp_type*)other.vals.a)[i];
    }
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other) const
{
    Matrix4x4 ret;

    for(uint32_t i = 0; i < 16; i++)
    {
        ((fp_type*)ret.vals.a)[i] = ((fp_type*)vals.a)[i] - ((fp_type*)other.vals.a)[i];
    }

    return ret;
}

void Matrix4x4::operator-=(const Matrix4x4& other)
{
    for(uint32_t i = 0; i < 16; i++)
    {
        ((fp_type*)vals.a)[i] -= ((fp_type*)other.vals.a)[i];
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
        ((fp_type*)ret.vals.a)[i] = ((fp_type*)vals.a)[i] * scalar;

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
        ((fp_type*)ret.vals.a)[i] = ((fp_type*)vals.a)[i] / scalar;

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
        ((fp_type*)ret.vals.a)[i] = -((fp_type*)vals.a)[i];

    return ret;
}

Vector3d Matrix4x4::translation() const
{
    return Vector3d(vals.d.f03, vals.d.f13, vals.d.f23);
}

#ifdef VECTOR_PRINT_PRECISION
std::ostream& operator<<(std::ostream& os, const Matrix4x4& m)
{
    os << "[" //<< std::setprecision(VECTOR_PRINT_PRECISION)
    << "[" << round(m.vals.d.f00 * pow(10, VECTOR_PRINT_PRECISION))/pow(10, VECTOR_PRINT_PRECISION) << ", "
           << round(m.vals.d.f01 * pow(10, VECTOR_PRINT_PRECISION))/pow(10, VECTOR_PRINT_PRECISION) << ", "
           << round(m.vals.d.f02 * pow(10, VECTOR_PRINT_PRECISION))/pow(10, VECTOR_PRINT_PRECISION) << ", "
           << round(m.vals.d.f03 * pow(10, VECTOR_PRINT_PRECISION))/pow(10, VECTOR_PRINT_PRECISION) << "], "
    << "[" << round(m.vals.d.f10 * pow(10, VECTOR_PRINT_PRECISION))/pow(10, VECTOR_PRINT_PRECISION) << ", "
           << round(m.vals.d.f11 * pow(10, VECTOR_PRINT_PRECISION))/pow(10, VECTOR_PRINT_PRECISION) << ", "
           << round(m.vals.d.f12 * pow(10, VECTOR_PRINT_PRECISION))/pow(10, VECTOR_PRINT_PRECISION) << ", "
           << round(m.vals.d.f13 * pow(10, VECTOR_PRINT_PRECISION))/pow(10, VECTOR_PRINT_PRECISION) << "], "
    << "[" << round(m.vals.d.f20 * pow(10, VECTOR_PRINT_PRECISION))/pow(10, VECTOR_PRINT_PRECISION) << ", "
           << round(m.vals.d.f21 * pow(10, VECTOR_PRINT_PRECISION))/pow(10, VECTOR_PRINT_PRECISION) << ", "
           << round(m.vals.d.f22 * pow(10, VECTOR_PRINT_PRECISION))/pow(10, VECTOR_PRINT_PRECISION) << ", "
           << round(m.vals.d.f23 * pow(10, VECTOR_PRINT_PRECISION))/pow(10, VECTOR_PRINT_PRECISION) << "], "
    << "[" << round(m.vals.d.f30 * pow(10, VECTOR_PRINT_PRECISION))/pow(10, VECTOR_PRINT_PRECISION) << ", "
           << round(m.vals.d.f31 * pow(10, VECTOR_PRINT_PRECISION))/pow(10, VECTOR_PRINT_PRECISION) << ", "
           << round(m.vals.d.f32 * pow(10, VECTOR_PRINT_PRECISION))/pow(10, VECTOR_PRINT_PRECISION) << ", "
           << round(m.vals.d.f33 * pow(10, VECTOR_PRINT_PRECISION))/pow(10, VECTOR_PRINT_PRECISION) << "]"
    << "]";
    return os;
}
#endif

#endif
