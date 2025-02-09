#ifndef HEIGHTMAPGENERATOR_H
#define HEIGHTMAPGENERATOR_H

#include "IHeightMapGenerator.h"
#include <vector>

class HeightMapGenerator {
public:
    static std::vector<std::vector<float>> generate(const std::string& type, int width, int height);
};

#endif // HEIGHTMAPGENERATOR_H