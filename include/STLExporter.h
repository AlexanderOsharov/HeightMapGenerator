#ifndef STLEXPORTER_H
#define STLEXPORTER_H

#include "HeightMap.h"
#include <string>

class STLExporter {
public:
    static void exportToFile(const HeightMap& heightMap, const std::string& filename);
};

#endif // STLEXPORTER_H