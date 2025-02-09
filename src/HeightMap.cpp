#include "HeightMap.h"

HeightMap::HeightMap(int width, int height)
    : m_data(height, std::vector<float>(width, 0.0f)) {}

void HeightMap::setData(const std::vector<std::vector<float>>& data) {
    m_data = data;
}

const std::vector<std::vector<float>>& HeightMap::getData() const {
    return m_data;
}