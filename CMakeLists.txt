cmake_minimum_required(VERSION 3.10)
project(HeightMapGenerator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем все исходные файлы
add_library(HeightMapGenerator STATIC
    src/HeightMap.cpp
    src/HeightMapFactory.cpp
    src/HeightMapCache.cpp
    src/PerlinNoiseGenerator.cpp
    src/SimplexNoiseGenerator.cpp
    src/CompositeHeightMapGenerator.cpp
    src/JSONExporter.cpp
    src/OBJExporter.cpp
    src/STLExporter.cpp
)

# Подключение заголовочных файлов
target_include_directories(HeightMapGenerator PUBLIC include)

# Экспортируем библиотеку
install(TARGETS HeightMapGenerator DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)