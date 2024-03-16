#include "stdafx.h"
#include "visualizer.h"
#include "openGLWindow.h"
#include "PathFinder.h"
#include "StlReader.h"

Visualizer::Visualizer(QWindow* parent) : QMainWindow(nullptr)
{
    setupUi();
}

Visualizer::~Visualizer()
{

}

void Visualizer::setupUi() 
{
    resize(600, 600);
    mCentralGrid = new QGridLayout(this);

    mReadStlFileButton = new QPushButton("Load STL file", this);
    mCentralGrid->addWidget(mReadStlFileButton, 0, 0);
    
    mRenderer = new OpenGLWindow(QColor(1,1,1), this);
    mCentralGrid->addWidget(mRenderer, 1, 0, 1, 0);

    mWidget = new QWidget(this);
    mWidget->setLayout(mCentralGrid);

    // signal slot connection
    connect(mReadStlFileButton, &QPushButton::clicked, this, &Visualizer::onLoadSTLFileButtonClicked);

    setCentralWidget(mWidget);
    setWindowTitle(QCoreApplication::translate("Visualiser", "WaterFlow Path Generator", nullptr));
}


// method triggered upon clicking "Load STL file" button
// (Triangulation, STLReader, PathFinder objects creation and member functions called)
void Visualizer::onLoadSTLFileButtonClicked()
{
    Shapes3D::Triangulation triangulation;
    FileReader::StlReader reader;
    reader.read("resources/terrain.stl", triangulation);

    PathFinding::PathFinder pathFinder(triangulation);
    vector<Geometry::Point3D> waterFlowPath = pathFinder.findWaterFlowPath();

    // pass triangulation-uniquePoints and waterFlowPath to OpenGLWindow for rendering
    mRenderer->setRenderAttributes(triangulation.uniquePoints(), waterFlowPath);
}