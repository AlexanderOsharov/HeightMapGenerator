#include "STLExporter.h"
#include <fstream>
#include <vector>

struct Triangle {
    float normal[3];
    float vertices[3][3];
};

void writeTriangle(std::ofstream& file, const Triangle& triangle) {
    file.write(reinterpret_cast<const char*>(triangle.normal), sizeof(float) * 3);
    for (int i = 0; i < 3; ++i) {
        file.write(reinterpret_cast<const char*>(triangle.vertices[i]), sizeof(float) * 3);
    }
    file.write("\0\0", 2); // Attribute byte count
}

void STLExporter::exportToFile(const HeightMap& heightMap, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing");
    }

    const auto& data = heightMap.getData();
    int height = data.size();
    int width = data[0].size();

    file.write("HeightMapGenerator", 80); // Header
    uint32_t numTriangles = 2 * (height - 1) * (width - 1);
    file.write(reinterpret_cast<const char*>(&numTriangles), sizeof(uint32_t));

    for (int y = 0; y < height - 1; ++y) {
        for (int x = 0; x < width - 1; ++x) {
            Triangle triangle1 = {{0, 0, 1}, {
                {x, data[y][x], y},
                {x + 1, data[y][x + 1], y},
                {x, data[y + 1][x], y + 1}
            }};
            writeTriangle(file, triangle1);

            Triangle triangle2 = {{0, 0, 1}, {
                {x + 1, data[y][x + 1], y},
                {x + 1, data[y + 1][x + 1], y + 1},
                {x, data[y + 1][x], y + 1}
            }};
            writeTriangle(file, triangle2);
        }
    }
}