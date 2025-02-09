#include "CompositeHeightMapGenerator.h"

void CompositeHeightMapGenerator::addGenerator(IHeightMapGenerator* generator) {
    m_generators.push_back(generator);
}

std::vector<std::vector<float>> CompositeHeightMapGenerator::generate(int width, int height) const {
    if (m_generators.empty()) {
        throw std::runtime_error("No generators added");
    }

    std::vector<std::vector<float>> result = m_generators[0]->generate(width, height);

    for (size_t i = 1; i < m_generators.size(); ++i) {
        std::vector<std::vector<float>> nextMap = m_generators[i]->generate(width, height);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                result[y][x] += nextMap[y][x];
            }
        }
    }

    return result;
}