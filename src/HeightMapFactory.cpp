#include "HeightMapFactory.h"
#include "PerlinNoiseGenerator.h"
#include "SimplexNoiseGenerator.h"
#include "CompositeHeightMapGenerator.h"

IHeightMapGenerator* HeightMapFactory::createGenerator(const std::string& type) {
    if (type == "perlin") {
        return new PerlinNoiseGenerator();
    } else if (type == "simplex") {
        return new SimplexNoiseGenerator();
    } else if (type == "composite") {
        CompositeHeightMapGenerator* composite = new CompositeHeightMapGenerator();
        composite->addGenerator(new PerlinNoiseGenerator());
        composite->addGenerator(new SimplexNoiseGenerator());
        return composite;
    }
    return nullptr;
}