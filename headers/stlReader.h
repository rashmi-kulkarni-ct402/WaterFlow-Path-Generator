#pragma once
#include "Triangulation.h"

#include <string>

namespace FileReader
{
    class StlReader
    {
    public:
        StlReader();
        ~StlReader();

        void read(const std::string& filePath, Shapes3D::Triangulation& triangulation);
    };
}