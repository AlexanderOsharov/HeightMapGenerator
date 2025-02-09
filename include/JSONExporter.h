#ifndef JSONEXPORTER_H
#define JSONEXPORTER_H

#include "HeightMap.h"
#include <string>

class JSONExporter {
public:
    static void exportToFile(const HeightMap& heightMap, const std::string& filename);
};

#endif // JSONEXPORTER_H