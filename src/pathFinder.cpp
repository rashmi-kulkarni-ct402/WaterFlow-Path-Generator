#include "stdafx.h"
#include "PathFinder.h"

#include<iostream>

// default ctor
PathFinding::PathFinder::PathFinder()
{

}

// parameterized ctor
PathFinding::PathFinder::PathFinder(const Shapes3D::Triangulation& inTriangulation) 
    : mTriangulation(inTriangulation)
{
    buildAdjacencyList();
}

// dtor
PathFinding::PathFinder::~PathFinder()
{

}

// creates adjacency list based on triangulation
void PathFinding::PathFinder::buildAdjacencyList()
{
    // initialize adjacency list with empty vectors for each unique point
    mAdjacencyList.resize(mTriangulation.uniquePoints().size());

    // iterate through each triangle to create adjacency list
    for (const auto& triangle : mTriangulation.triangles())
    {
        int index1 = triangle.index1();
        int index2 = triangle.index2();
        int index3 = triangle.index3();

        // add edges between the vertices of triangle
        mAdjacencyList[index1].push_back(index2);
        mAdjacencyList[index1].push_back(index3);
        mAdjacencyList[index2].push_back(index1);
        mAdjacencyList[index2].push_back(index3);
        mAdjacencyList[index3].push_back(index1);
        mAdjacencyList[index3].push_back(index2);
    }
}

// finds the highest point on terrain
Geometry::Point3D PathFinding::PathFinder::findHighestPoint() const
{
    // start with first point as highest point
    Geometry::Point3D highestPoint = mTriangulation.uniquePoints().front();

    // iterate through all unique points to find the highest point
    for (const auto& point : mTriangulation.uniquePoints())
    {
        if (point.y() > highestPoint.y())
        {
            highestPoint = point;
        }
    }
    return highestPoint;
}

// finds neighboring points for a given point
vector<Geometry::Point3D> PathFinding::PathFinder::getNeighbors(const Geometry::Point3D& point)
{
    vector<Geometry::Point3D> neighbors;

    // find index of given point in uniquePoints vetcor
    int index = -1;

    for (int i = 0; i < mTriangulation.uniquePoints().size(); ++i) 
    {
        if (mTriangulation.uniquePoints()[i] == point)
        {
            index = static_cast<int>(i);
            break;
        }
    }

    // get neighboring indices if point is found
    if (index != -1) 
    {
        for (int neighborIndex : mAdjacencyList[index]) 
        {
            if (neighborIndex >= 0 && neighborIndex < mTriangulation.uniquePoints().size()) 
            {
                neighbors.push_back(mTriangulation.uniquePoints()[neighborIndex]);
            }
        }
    }
    return neighbors;
}


//  finds next point in flow path from current point
Geometry::Point3D PathFinding::PathFinder::findPathFromPoint(const Geometry::Point3D& currentPoint)
{
    // assign all neighboring points of current point in "neighbors" vector
    std::vector<Geometry::Point3D> neighbors = getNeighbors(currentPoint);

    Geometry::Point3D nextPoint = currentPoint;

    double lowestHeight = currentPoint.y();
    
    // iterate through all neighboring points to find the point with lowest height
    for (const auto& neighbor : neighbors) 
    {
        if (neighbor.y() < lowestHeight) 
        {
            lowestHeight = neighbor.y();
            nextPoint = neighbor;
        }
    }
    return nextPoint;
}

// finds water flow path from the highest point
std::vector<Geometry::Point3D> PathFinding::PathFinder::findWaterFlowPath()
{
    std::vector<Geometry::Point3D> waterFlowPath;

    // get value of highest poitnon terrain and add to waterFlowPath vector
    Geometry::Point3D currentPoint = findHighestPoint();
    waterFlowPath.push_back(currentPoint);

    // iterations limit to prevent infinite loop
    const int maxIterations = 10000;
    int iterationCount = 0;

    // find water flow path until no lower neighbor is found
    while (iterationCount < maxIterations)
    {
        // find next point from current point
        Geometry::Point3D nextPoint = findPathFromPoint(currentPoint);

        // if next point is equal or higher than current point, stop
        if (nextPoint.y() >= currentPoint.y()) 
        {
            break;
        }
        
        // add next point in waterFlowPath vector
        waterFlowPath.push_back(nextPoint);
        
        // assign next point as current point for next iteration
        currentPoint = nextPoint;
        iterationCount++;
    }

    if (iterationCount >= maxIterations)
    {
        std::cerr << "Max iterations reached -> possible infinite loop issue." << std::endl;
    }

    return waterFlowPath;
}
