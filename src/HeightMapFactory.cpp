#include "HeightMapFactory.h"
#include "PerlinNoiseGenerator.h" // Предполагается, что этот класс уже реализован

IHeightMapGenerator* HeightMapFactory::createGenerator(const std::string& type) {
    if (type == "perlin") {
        return new PerlinNoiseGenerator();
    }
    // Добавьте другие типы генераторов здесь
    return nullptr;
}