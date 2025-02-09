#include "OBJExporter.h"
#include <fstream>
#include <iomanip>

void OBJExporter::exportToFile(const HeightMap& heightMap, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing");
    }

    const auto& data = heightMap.getData();
    int height = data.size();
    int width = data[0].size();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            file << "v " << x << " " << data[y][x] << " " << y << "\n";
        }
    }

    for (int y = 0; y < height - 1; ++y) {
        for (int x = 0; x < width - 1; ++x) {
            int idx = y * width + x + 1;
            file << "f " << idx << " " << idx + 1 << " " << idx + width + 1 << "\n";
            file << "f " << idx << " " << idx + width + 1 << " " << idx + width << "\n";
        }
    }
}