#include "SimplexNoiseGenerator.h"
#include <vector>
#include <cmath>

SimplexNoiseGenerator::SimplexNoiseGenerator(int octaves, float persistence, float scale)
    : m_octaves(octaves), m_persistence(persistence), m_scale(scale) {}

std::vector<std::vector<float>> SimplexNoiseGenerator::generate(int width, int height) const {
    std::vector<std::vector<float>> result(height, std::vector<float>(width, 0.0f));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float amplitude = 1.0f;
            float frequency = 1.0f;
            float total = 0.0f;

            for (int i = 0; i < m_octaves; ++i) {
                total += simplexNoise(x * frequency * m_scale, y * frequency * m_scale) * amplitude;
                amplitude *= m_persistence;
                frequency *= 2.0f;
            }

            result[y][x] = total;
        }
    }

    return result;
}

float SimplexNoiseGenerator::simplexNoise(float xin, float yin) const {
    float F2 = 0.5f * (std::sqrt(3.0f) - 1.0f);
    float G2 = (3.0f - std::sqrt(3.0f)) / 6.0f;

    float s = (xin + yin) * F2;
    int i = static_cast<int>(std::floor(xin + s));
    int j = static_cast<int>(std::floor(yin + s));

    float t = (i + j) * G2;
    float X0 = i - t;
    float Y0 = j - t;
    float x0 = xin - X0;
    float y0 = yin - Y0;

    int i1, j1;
    if (x0 > y0) {
        i1 = 1;
        j1 = 0;
    } else {
        i1 = 0;
        j1 = 1;
    }

    float x1 = x0 - i1 + G2;
    float y1 = y0 - j1 + G2;
    float x2 = x0 - 1.0f + 2.0f * G2;
    float y2 = y0 - 1.0f + 2.0f * G2;

    int ii = i & 255;
    int jj = j & 255;

    float t0 = 0.5f - x0 * x0 - y0 * y0;
    float n0 = t0 < 0 ? 0.0f : t0 * t0 * grad(ii + jj, x0, y0);

    float t1 = 0.5f - x1 * x1 - y1 * y1;
    float n1 = t1 < 0 ? 0.0f : t1 * t1 * grad(ii + i1 + jj + j1, x1, y1);

    float t2 = 0.5f - x2 * x2 - y2 * y2;
    float n2 = t2 < 0 ? 0.0f : t2 * t2 * grad(ii + 1 + jj + 1, x2, y2);

    return 70.0f * (n0 + n1 + n2);
}

float SimplexNoiseGenerator::fade(float t) {
    return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
}

float SimplexNoiseGenerator::lerp(float t, float a, float b) {
    return a + t * (b - a);
}

float SimplexNoiseGenerator::grad(int hash, float x, float y) {
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : (h == 12 || h == 14 ? x : 0.0f);
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}