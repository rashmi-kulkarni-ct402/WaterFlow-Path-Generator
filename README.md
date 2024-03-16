# WaterFlow-Path-Generator
This project is designed to analyze a given terrain represented as an STL file and find the path of water flow on that terrain. It uses C++ with the Qt framework and OpenGL for rendering the terrain and the calculated water flow path.
 
## Features
**STL File Reading:** Reads an STL file and constructs a triangulated representation of the terrain.

**Water Flow Path Calculation:** Calculates the path that water would take from the highest point of the terrain to the lowest point.

**3D Visualization:** Visualizes the terrain and the water flow path in a 3D OpenGL window.

**Interactive UI:** Provides a simple user interface to load STL files and view the terrain and water flow path.
 
## Classes
**Geometry::Point3D:** Represents a 3D point with x, y, and z coordinates.

**Geometry::Triangle:** Represents a triangle with three vertex indices.

**Shapes3D::Triangulation:** Stores unique points and triangles of the terrain.

**FileReader::StlReader:** Reads STL files and populates a Shapes3D::Triangulation object.

**PathFinding::PathFinder:** Calculates the water flow path on the terrain.

**OpenGLWindow:** Inherits from QOpenGLWidget and handles rendering of the terrain and water flow path.

**Visualizer:** Inherits from QMainWindow and provides the main window and UI for the application.
 
## Output
The application visualizes the terrain and the water flow path in a 3D OpenGL window. The terrain is rendered in a solid color, while the water flow path is highlighted for easy identification.

<img width="443" alt="WaterFlowPath" src="https://github.com/rashmi-kulkarni-ct402/WaterFlow-Path-Generator/assets/158051740/ce3dba7d-0143-4337-a067-a792c7617097">
