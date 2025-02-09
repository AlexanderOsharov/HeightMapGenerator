#ifndef HEIGHTMAPFACTORY_H
#define HEIGHTMAPFACTORY_H

#include "IHeightMapGenerator.h"

class HeightMapFactory {
public:
    static IHeightMapGenerator* createGenerator(const std::string& type);
};

#endif // HEIGHTMAPFACTORY_H