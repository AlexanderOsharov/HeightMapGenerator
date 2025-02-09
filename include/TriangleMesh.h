#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include <vector>
#include <array>

// Структура вершины
struct Vertex {
    std::array<float, 3> position; // x, y, z координаты
    std::array<float, 3> normal;   // нормаль
};

// Структура треугольника
struct Triangle {
    std::array<int, 3> indices; // Индексы вершин
};

class TriangleMesh {
public:
    // Получение вершин
    const std::vector<Vertex>& getVertices() const;
    
    // Получение треугольников
    const std::vector<Triangle>& getTriangles() const;

    // Добавление вершины
    void addVertex(const std::array<float, 3>& position);
    
    // Добавление треугольника
    void addTriangle(int v1, int v2, int v3);

    // Расчет нормалей
    void calculateNormals();

private:
    std::vector<Vertex> vertices;
    std::vector<Triangle> triangles;
};

#endif // TRIANGLEMESH_H