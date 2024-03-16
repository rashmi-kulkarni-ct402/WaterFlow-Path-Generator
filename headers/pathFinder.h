#pragma once
#include "Triangulation.h"
#include <queue>
#include <vector>
#include <limits>

using namespace std;

namespace PathFinding
{
    class PathFinder
    {
    public:
        PathFinder();
        PathFinder(const Shapes3D::Triangulation& inTriangulation);
        ~PathFinder();
        
        vector<Geometry::Point3D> findWaterFlowPath();

    private:      
        void buildAdjacencyList();
        Geometry::Point3D findHighestPoint() const;
        vector<Geometry::Point3D> findNeighbors(const Geometry::Point3D& point);
        Geometry::Point3D findPathFromPoint(const Geometry::Point3D& currentPoint); 

        Shapes3D::Triangulation mTriangulation;
        vector<Geometry::Point3D> mWaterFlowPath;
        vector<vector<int>> mAdjacencyList;
    };
}


      
