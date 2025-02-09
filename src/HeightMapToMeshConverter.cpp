#include "HeightMapToMeshConverter.h"
#include "Mesh.h"
#include "HeightMap.h"

Mesh HeightMapToMeshConverter::convert(const HeightMap& heightMap) {
    Mesh mesh;

    const auto& data = heightMap.getData();
    int width = heightMap.getWidth();
    int height = heightMap.getHeight();

    // Добавление вершин
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float z = data[y][x];
            mesh.addVertex(x, z, y);
        }
    }

    // Добавление граней
    for (int y = 0; y < height - 1; ++y) {
        for (int x = 0; x < width - 1; ++x) {
            int idx = y * width + x;
            mesh.addFace(idx, idx + 1, idx + width + 1);
            mesh.addFace(idx, idx + width + 1, idx + width);
        }
    }

    return mesh;
}