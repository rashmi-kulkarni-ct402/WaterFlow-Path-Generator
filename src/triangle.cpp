#include "stdafx.h"
#include "Triangle.h"

Geometry::Triangle::Triangle() : mIndex1(0), mIndex2(0), mIndex3(0) {}
Geometry::Triangle::Triangle(const int inIndex1, const int inIndex2, const int inIndex3) : mIndex1(inIndex1), mIndex2(inIndex2), mIndex3(inIndex3) {}
Geometry::Triangle::~Triangle() {}

// getter methods
int Geometry::Triangle::index1() const
{
    return mIndex1;
}

int Geometry::Triangle::index2() const
{
    return mIndex2;
}

int Geometry::Triangle::index3() const
{
    return mIndex3;
}

// setter methods
void Geometry::Triangle::setindex1(int inIndex1)
{
    mIndex1 = inIndex1;
}

void Geometry::Triangle::setindex2(int inIndex2)
{
    mIndex2 = inIndex2;
}

void Geometry::Triangle::setindex3(int inIndex3)
{
    mIndex3 = inIndex3;
}
