#ifndef HEIGHTMAPCACHE_H
#define HEIGHTMAPCACHE_H

#include <unordered_map>
#include <vector>
#include <string>

class HeightMapCache {
public:
    static std::vector<std::vector<float>> getOrGenerate(const std::string& generatorType,
                                                         int width, int height,
                                                         const std::vector<float>& params);

private:
    static std::unordered_map<std::string, std::vector<std::vector<float>>> cache_;
};

#endif // HEIGHTMAPCACHE_H