#pragma once
#include "Point3D.h"
#include "Triangle.h"

using namespace std;

namespace Shapes3D
{
    class Triangulation
    {
    public:
        Triangulation();
        ~Triangulation();

        vector<Geometry::Point3D> uniquePoints() const;
        vector<Geometry::Triangle> triangles() const;
        void addUniquePointToTriangulation(const Geometry::Point3D inPoint);
        void addTriangleToTriangulation(const Geometry::Triangle inTriangle);

    private:
        vector<Geometry::Point3D> mUniquePoints;
        vector<Geometry::Triangle> mTriangles;
    };
}