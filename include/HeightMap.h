#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <vector>

class HeightMap {
public:
    HeightMap(int width, int height);

    void setData(const std::vector<std::vector<float>>& data);
    const std::vector<std::vector<float>>& getData() const;

private:
    std::vector<std::vector<float>> m_data;
};

#endif // HEIGHTMAP_H