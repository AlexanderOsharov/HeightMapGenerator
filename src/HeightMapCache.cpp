#include "HeightMapCache.h"
#include "HeightMapFactory.h"

std::unordered_map<std::string, std::vector<std::vector<float>>> HeightMapCache::cache_;

std::vector<std::vector<float>> HeightMapCache::getOrGenerate(const std::string& generatorType,
                                                              int width, int height,
                                                              const std::vector<float>& params) {
    std::string key = generatorType + "_" + std::to_string(width) + "_" + std::to_string(height);
    for (float param : params) {
        key += "_" + std::to_string(param);
    }

    if (cache_.find(key) != cache_.end()) {
        return cache_[key];
    }

    IHeightMapGenerator* generator = HeightMapFactory::createGenerator(generatorType);
    if (!generator) {
        throw std::runtime_error("Unknown generator type");
    }

    std::vector<std::vector<float>> result = generator->generate(width, height);
    cache_[key] = result;
    delete generator;

    return result;
}