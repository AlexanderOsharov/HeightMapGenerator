#include "JSONExporter.h"
#include <fstream>
#include <iomanip>

void JSONExporter::exportToFile(const HeightMap& heightMap, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing");
    }

    const auto& data = heightMap.getData();
    file << "{ \"heightMap\": [\n";

    for (size_t y = 0; y < data.size(); ++y) {
        file << "  [";
        for (size_t x = 0; x < data[y].size(); ++x) {
            file << data[y][x];
            if (x != data[y].size() - 1) file << ", ";
        }
        file << "]";
        if (y != data.size() - 1) file << ",";
        file << "\n";
    }

    file << "]}\n";
}