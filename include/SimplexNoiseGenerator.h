#ifndef SIMPLEXNOISEGENERATOR_H
#define SIMPLEXNOISEGENERATOR_H

#include "IHeightMapGenerator.h"
#include <vector>
#include <cmath>

class SimplexNoiseGenerator : public IHeightMapGenerator {
public:
    SimplexNoiseGenerator(int octaves = 6, float persistence = 0.5f, float scale = 0.01f);

    std::vector<std::vector<float>> generate(int width, int height) const override;

private:
    int m_octaves;
    float m_persistence;
    float m_scale;

    float simplexNoise(float x, float y) const;
    static float fade(float t);
    static float lerp(float t, float a, float b);
    static float grad(int hash, float x, float y);
};

#endif // SIMPLEXNOISEGENERATOR_H