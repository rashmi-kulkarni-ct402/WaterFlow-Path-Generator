#pragma once
#include "Point3D.h"

namespace Geometry
{
    class Triangle
    {
    public:
        Triangle();
        Triangle(const int inIndex1, const int inIndex2, const int inIndex3);
        ~Triangle();

        int index1() const;
        int index2() const;
        int index3() const;

        void setindex1(int inIndex1);
        void setindex2(int inIndex2);
        void setindex3(int inIndex3);

    private:
        int mIndex1;
        int mIndex2;
        int mIndex3;
    };
}
