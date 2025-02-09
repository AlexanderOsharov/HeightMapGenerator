#ifndef OBJEXPORTER_H
#define OBJEXPORTER_H

#include "HeightMap.h"
#include <string>

class OBJExporter {
public:
    static void exportToFile(const HeightMap& heightMap, const std::string& filename);
};

#endif // OBJEXPORTER_H