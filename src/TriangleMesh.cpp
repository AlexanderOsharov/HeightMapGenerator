#include "TriangleMesh.h"

const std::vector<Vertex>& TriangleMesh::getVertices() const {
    return vertices;
}

const std::vector<Triangle>& TriangleMesh::getTriangles() const {
    return triangles;
}

void TriangleMesh::addVertex(const std::array<float, 3>& position) {
    vertices.emplace_back(Vertex{position, {0.0f, 0.0f, 0.0f}});
}

void TriangleMesh::addTriangle(int v1, int v2, int v3) {
    triangles.emplace_back(Triangle{{v1, v2, v3}});
}

void TriangleMesh::calculateNormals() {
    for(auto& triangle : triangles) {
        // Получаем позиции вершин треугольника
        const auto& v1 = vertices[triangle.indices[0]].position;
        const auto& v2 = vertices[triangle.indices[1]].position;
        const auto& v3 = vertices[triangle.indices[2]].position;

        // Вычисляем вектора сторон
        std::array<float, 3> edge1 = {v2[0] - v1[0], v2[1] - v1[1], v2[2] - v1[2]};
        std::array<float, 3> edge2 = {v3[0] - v1[0], v3[1] - v1[1], v3[2] - v1[2]};

        // Вычисляем векторное произведение
        std::array<float, 3> normal = {
            edge1[1] * edge2[2] - edge1[2] * edge2[1],
            edge1[2] * edge2[0] - edge1[0] * edge2[2],
            edge1[0] * edge2[1] - edge1[1] * edge2[0]
        };

        // Добавляем нормаль к каждой вершине треугольника
        for(auto index : triangle.indices) {
            vertices[index].normal[0] += normal[0];
            vertices[index].normal[1] += normal[1];
            vertices[index].normal[2] += normal[2];
        }
    }

    // Нормализация нормалей
    for(auto& vertex : vertices) {
        float length = std::sqrt(
            vertex.normal[0] * vertex.normal[0] +
            vertex.normal[1] * vertex.normal[1] +
            vertex.normal[2] * vertex.normal[2]
        );
        if(length > 0.0f) {
            vertex.normal[0] /= length;
            vertex.normal[1] /= length;
            vertex.normal[2] /= length;
        }
    }
}