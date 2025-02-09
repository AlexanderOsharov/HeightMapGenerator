#ifndef HEIGHTMAPTOMESHCONVERTER_H
#define HEIGHTMAPTOMESHCONVERTER_H

#include "TriangleMesh.h"
#include <vector>

class HeightMapToMeshConverter {
public:
    static TriangleMesh convert(const std::vector<std::vector<float>>& heightMap, float scale = 1.0f);
};

#endif // HEIGHTMAPTOMESHCONVERTER_H