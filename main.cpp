#include "stdafx.h"
#include "Visualizer.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    Visualizer mainWindow;
    mainWindow.show();
    return a.exec();
}
