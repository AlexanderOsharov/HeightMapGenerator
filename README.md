# HeightMapGenerator

## Описание
Библиотека для генерации карт высот с использованием различных алгоритмов (Perlin Noise, Simplex Noise и др.).

## Установка
1. Клонируйте репозиторий:
   ```bash
   git clone https://github.com/AlexanderOsharov/HeightMapGenerator.git
   ```
2. Скомпилируйте библиотеку
   ```bash
   cmake .
   make
   ```
## Использование
Пример кода
```C++
#include "PerlinNoiseGenerator.h"
#include "HeightMap.h"

int main() {
    PerlinNoiseGenerator generator(6, 0.5f, 0.01f);
    HeightMap heightMap(100, 100);
    heightMap.setData(generator.generate(100, 100));

    // Экспорт в OBJ
    OBJExporter::exportToFile(heightMap, "output.obj");

    return 0;
}
```

## Функциональность
1. Генерация карт высот с использованием Perlin Noise.
2. Генерация карт высот с использованием Simplex Noise.
3. Объединение нескольких алгоритмов.
4. Экспорт в форматы OBJ, STL.
