#ifndef COMPOSITEHEIGHTMAPGENERATOR_H
#define COMPOSITEHEIGHTMAPGENERATOR_H

#include "IHeightMapGenerator.h"
#include <vector>

class CompositeHeightMapGenerator : public IHeightMapGenerator {
public:
    void addGenerator(IHeightMapGenerator* generator);
    std::vector<std::vector<float>> generate(int width, int height) const override;

private:
    std::vector<IHeightMapGenerator*> m_generators;
};

#endif // COMPOSITEHEIGHTMAPGENERATOR_H