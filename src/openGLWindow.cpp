#include "stdafx.h"
#include "openGLWindow.h"

#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <iostream>
#include <Qscreen>
#include <QMatrix4x4>

OpenGLWindow::OpenGLWindow(const QColor& background, QMainWindow* parent) :
    mBackground(background)
{
    setParent(parent);
    setMinimumSize(300, 250);
}

OpenGLWindow::~OpenGLWindow()
{
    reset();
}

void OpenGLWindow::reset()
{
    makeCurrent();
    delete mProgram;
    mProgram = nullptr;
    delete mVshader;
    mVbo.destroy();
    doneCurrent();
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent* event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();
    if (event->buttons() & Qt::LeftButton)
    {
        QQuaternion rotX = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 0.5f * dx);
        QQuaternion rotY = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 0.5f * dy);

        rotationAngle = rotX * rotY * rotationAngle;
        update();
    }
    lastPos = event->pos();
}

void OpenGLWindow::wheelEvent(QWheelEvent* event)
{
    if (event->angleDelta().y() > 0)
    {
        zoomOut();
    }
    else
    {
        zoomIn();
    }
}

void OpenGLWindow::zoomIn()
{
    scaleFactor *= 1.1f;
    update();
}

void OpenGLWindow::zoomOut()
{
    scaleFactor /= 1.1f;
    update();
}

void OpenGLWindow::initializeGL()
{
    static const char* vertexShaderSource =
        "attribute highp vec4 posAttr;\n"
        "attribute lowp vec4 colAttr;\n"
        "varying lowp vec4 col;\n"
        "uniform highp mat4 matrix;\n"
        "void main() {\n"
        "   col = colAttr;\n"
        "   gl_Position = matrix * posAttr;\n"
        "}\n";

    static const char* fragmentShaderSource =
        "varying lowp vec4 col;\n"
        "void main() {\n"
        "   gl_FragColor = col;\n"
        "}\n";

    rotationAngle = QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 1.0f, 0.0f);

    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->link();
    m_posAttr = mProgram->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_colAttr = mProgram->attributeLocation("colAttr");
    Q_ASSERT(m_colAttr != -1);
    m_matrixUniform = mProgram->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);
}

void OpenGLWindow::setRenderAttributes(const vector<Geometry::Point3D>& inTerrainVertices, 
    const vector<Geometry::Point3D>& inWaterFlowPathVertices)
{
    mTerrainVertices.clear();
    mTerrainColors.clear();
    mWaterFlowPathVertices.clear();
    mWaterFlowPathColors.clear();

    for (const auto& point : inTerrainVertices) 
    {
        mTerrainVertices.push_back((point.x()));
        mTerrainVertices.push_back((point.y()));
        mTerrainVertices.push_back((point.z()));

        // olive green color
        mTerrainColors.push_back(0.502f); 
        mTerrainColors.push_back(0.502f); 
        mTerrainColors.push_back(0.0f); 
    }

    for (const auto& point : inWaterFlowPathVertices) 
    {
        mWaterFlowPathVertices.push_back((point.x()));
        mWaterFlowPathVertices.push_back((point.y()));
        mWaterFlowPathVertices.push_back((point.z()));

        // electric blue color
        mWaterFlowPathColors.push_back(0.0f); 
        mWaterFlowPathColors.push_back(1.0f); 
        mWaterFlowPathColors.push_back(1.0f); 
    }
    update();
}

void OpenGLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mProgram->bind();

    QMatrix4x4 matrix;
    matrix.ortho(-100.0f * scaleFactor, 100.0f * scaleFactor, -100.0f * scaleFactor, 100.0f * scaleFactor, 0.00000000001f, 1000000.0f);
    matrix.translate(0, 0, -15);
    matrix.rotate(rotationAngle);

    mProgram->setUniformValue(m_matrixUniform, matrix);

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    glVertexAttribPointer(m_posAttr, 3, GL_DOUBLE, GL_FALSE, 0, mTerrainVertices.data());
    glVertexAttribPointer(m_colAttr, 3, GL_DOUBLE, GL_FALSE, 0, mTerrainColors.data());
    glDrawArrays(GL_LINES, 0, mTerrainVertices.size() / 3);

    glLineWidth(10.0f);
    glVertexAttribPointer(m_posAttr, 3, GL_DOUBLE, GL_FALSE, 0, mWaterFlowPathVertices.data());
    glVertexAttribPointer(m_colAttr, 3, GL_DOUBLE, GL_FALSE, 0, mWaterFlowPathColors.data());
    glDrawArrays(GL_LINES, 0, mWaterFlowPathVertices.size() / 3);

    mProgram->disableAttributeArray(m_posAttr);
    mProgram->disableAttributeArray(m_colAttr);

    mProgram->release();
}