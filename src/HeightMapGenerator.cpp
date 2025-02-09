#include "HeightMapGenerator.h"
#include "HeightMapFactory.h"

std::vector<std::vector<float>> HeightMapGenerator::generate(const std::string& type, int width, int height) {
    IHeightMapGenerator* generator = HeightMapFactory::createGenerator(type);
    if (!generator) {
        throw std::runtime_error("Unknown generator type");
    }

    std::vector<std::vector<float>> result = generator->generate(width, height);
    delete generator;
    return result;
}