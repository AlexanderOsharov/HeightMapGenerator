#ifndef PERLINNOISEGENERATOR_H
#define PERLINNOISEGENERATOR_H

#include "IHeightMapGenerator.h"
#include <vector>
#include <cmath>

class PerlinNoiseGenerator : public IHeightMapGenerator {
public:
    PerlinNoiseGenerator(int octaves = 6, float persistence = 0.5f, float scale = 0.01f);

    std::vector<std::vector<float>> generate(int width, int height) const override;
    std::vector<std::vector<float>> generateParallel(int width, int height, int numThreads) const;

private:
    int m_octaves;
    float m_persistence;
    float m_scale;

    float perlinNoise(float x, float y) const;
    float interpolate(float a, float b, float t) const;
    float dotGridGradient(int ix, int iy, float x, float y) const;
    static std::vector<std::vector<float>> generateGradients(int gridSize);
};

#endif // PERLINNOISEGENERATOR_H