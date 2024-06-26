#include "stdafx.h"
#include "Point3D.h"
#include <cmath>

Geometry::Point3D::Point3D() : mX(), mY(), mZ() {}
Geometry::Point3D::Point3D(double inX, double inY, double inZ) : mX(inX), mY(inY), mZ(inZ) {}
Geometry::Point3D::~Point3D() {}

double Geometry::Point3D::x() const
{
    return mX;
}

double Geometry::Point3D::y() const
{
    return mY;
}

double Geometry::Point3D::z() const
{
    return mZ;
}

// less than operator overloading
bool Geometry::Point3D::operator<(const Point3D& other) const
{
    if (mX < other.mX)
        return true;
    if (mX > other.mX)
        return false;

    if (mY < other.mY)
        return true;
    if (mY > other.mY)
        return false;

    return mZ < other.mZ;
}

// equality operator overloading
bool Geometry::Point3D::operator==(const Point3D& other) const
{
    return mX == other.mX && mY == other.mY && mZ == other.mZ;
}