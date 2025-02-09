#ifndef IHEIGHTMAPGENERATOR_H
#define IHEIGHTMAPGENERATOR_H

#include <vector>

class IHeightMapGenerator {
public:
    virtual ~IHeightMapGenerator() = default;

    // Генерирует карту высот
    virtual std::vector<std::vector<float>> generate(int width, int height) const = 0;
};

#endif // IHEIGHTMAPGENERATOR_H