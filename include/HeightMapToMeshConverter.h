#ifndef HEIGHTMAPTOMESHCONVERTER_H
#define HEIGHTMAPTOMESHCONVERTER_H

#include "Mesh.h"
#include "HeightMap.h"

class HeightMapToMeshConverter {
public:
    static Mesh convert(const HeightMap& heightMap);
};

#endif // HEIGHTMAPTOMESHCONVERTER_H