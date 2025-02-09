#include "STLExporter.h"
#include <vector>

void STLExporter::exportToFile(const std::vector<std::array<float, 3>>& vertices, const std::vector<std::array<int, 3>>& triangles, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing");
    }

    // Write header
    char header[80] = {0};
    file.write(header, 80);

    // Write number of triangles
    uint32_t numTriangles = static_cast<uint32_t>(triangles.size());
    file.write(reinterpret_cast<char*>(&numTriangles), sizeof(uint32_t));

    for (const auto& triangle : triangles) {
        // Calculate normal
        std::array<float, 3> v1 = vertices[triangle[1]] - vertices[triangle[0]];
        std::array<float, 3> v2 = vertices[triangle[2]] - vertices[triangle[0]];
        std::array<float, 3> normal = crossProduct(v1, v2);

        // Normalize normal
        float length = std::sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
        if (length > 0.0f) {
            normal[0] /= length;
            normal[1] /= length;
            normal[2] /= length;
        }

        // Write normal
        file.write(reinterpret_cast<char*>(normal.data()), sizeof(float) * 3);

        // Write vertices
        for (int i = 0; i < 3; ++i) {
            file.write(reinterpret_cast<char*>(vertices[triangle[i]].data()), sizeof(float) * 3);
        }

        // Write attribute byte count
        uint16_t attributeByteCount = 0;
        file.write(reinterpret_cast<char*>(&attributeByteCount), sizeof(uint16_t));
    }
}

std::array<float, 3> STLExporter::crossProduct(const std::array<float, 3>& a, const std::array<float, 3>& b) {
    return {{
        a[1] * b[2] - a[2] * b[1],
        a[2] * b[0] - a[0] * b[2],
        a[0] * b[1] - a[1] * b[0]
    }};
}