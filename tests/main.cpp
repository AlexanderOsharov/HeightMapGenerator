#include <iostream>
#include "HeightMapFactory.h"
#include "HeightMap.h"

int main() {
    auto generator = HeightMapFactory::createGenerator("perlin");
    if (!generator) {
        std::cerr << "Failed to create generator" << std::endl;
        return 1;
    }

    HeightMap heightMap(100, 100);
    heightMap.setData(generator->generate(100, 100));

    std::cout << "Height map generated successfully!" << std::endl;

    delete generator;
    return 0;
}