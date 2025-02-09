#include "PerlinNoiseGenerator.h"
#include <thread>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>

PerlinNoiseGenerator::PerlinNoiseGenerator(int octaves, float persistence, float scale)
    : m_octaves(octaves), m_persistence(persistence), m_scale(scale) {}

std::vector<std::vector<float>> PerlinNoiseGenerator::generate(int width, int height) const {
    std::vector<std::vector<float>> result(height, std::vector<float>(width, 0.0f));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float amplitude = 1.0f;
            float frequency = 1.0f;
            float total = 0.0f;

            for (int i = 0; i < m_octaves; ++i) {
                total += perlinNoise(x * frequency * m_scale, y * frequency * m_scale) * amplitude;
                amplitude *= m_persistence;
                frequency *= 2.0f;
            }

            result[y][x] = total;
        }
    }

    return result;
}

std::vector<std::vector<float>> PerlinNoiseGenerator::generateParallel(int width, int height, int numThreads) const {
    std::vector<std::vector<float>> result(height, std::vector<float>(width, 0.0f));
    std::vector<std::thread> threads;

    auto generateRow = [this, &result, width](int startRow, int endRow) {
        for (int y = startRow; y < endRow; ++y) {
            for (int x = 0; x < width; ++x) {
                float amplitude = 1.0f;
                float frequency = 1.0f;
                float total = 0.0f;

                for (int i = 0; i < m_octaves; ++i) {
                    total += perlinNoise(x * frequency * m_scale, y * frequency * m_scale) * amplitude;
                    amplitude *= m_persistence;
                    frequency *= 2.0f;
                }

                result[y][x] = total;
            }
        }
    };

    int rowsPerThread = height / numThreads;
    int remainingRows = height % numThreads;

    int startRow = 0;
    for (int i = 0; i < numThreads; ++i) {
        int endRow = startRow + rowsPerThread + (i < remainingRows ? 1 : 0);
        threads.emplace_back(generateRow, startRow, endRow);
        startRow = endRow;
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return result;
}

float PerlinNoiseGenerator::perlinNoise(float x, float y) const {
    int X = static_cast<int>(std::floor(x)) & 255;
    int Y = static_cast<int>(std::floor(y)) & 255;

    float xf = x - std::floor(x);
    float yf = y - std::floor(y);

    std::vector<std::vector<float>> gradients = generateGradients(256);

    float n0 = dotGridGradient(X, Y, xf, yf);
    float n1 = dotGridGradient(X + 1, Y, xf - 1, yf);
    float ix0 = interpolate(n0, n1, xf);

    float n2 = dotGridGradient(X, Y + 1, xf, yf - 1);
    float n3 = dotGridGradient(X + 1, Y + 1, xf - 1, yf - 1);
    float ix1 = interpolate(n2, n3, xf);

    return 0.5f * (interpolate(ix0, ix1, yf) + 1.0f);
}

float PerlinNoiseGenerator::interpolate(float a, float b, float t) const {
    float ft = t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
    return a + ft * (b - a);
}

float PerlinNoiseGenerator::dotGridGradient(int ix, int iy, float x, float y) const {
    static std::vector<std::vector<float>> gradients = generateGradients(256);

    int gradientIndex = (ix + iy) % 256;
    float gx = gradients[gradientIndex][0];
    float gy = gradients[gradientIndex][1];

    return (gx * x + gy * y);
}

std::vector<std::vector<float>> PerlinNoiseGenerator::generateGradients(int gridSize) {
    static std::vector<std::vector<float>> gradients(gridSize, std::vector<float>(2, 0.0f));

    if (!gradients.empty()) {
        return gradients;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-1.0f, 1.0f);

    for (int i = 0; i < gridSize; ++i) {
        float angle = dis(gen) * 2.0f * M_PI;
        gradients[i][0] = std::cos(angle);
        gradients[i][1] = std::sin(angle);
    }

    return gradients;
}