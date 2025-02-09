cmake_minimum_required(VERSION 3.15)
project(HeightMapGenerator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем ImageProcessingLibrary как зависимость
find_package(Git REQUIRED)
if(NOT EXISTS "${CMAKE_BINARY_DIR}/ImageProcessingLibrary")
    message(STATUS "Cloning ImageProcessingLibrary...")
    execute_process(
        COMMAND ${GIT_EXECUTABLE} clone https://github.com/AlexanderOsharov/ImageProcessingLibrary.git ${CMAKE_BINARY_DIR}/ImageProcessingLibrary
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        RESULT_VARIABLE GIT_CLONE_RESULT
    )
    if(NOT GIT_CLONE_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone ImageProcessingLibrary")
    endif()
endif()

add_subdirectory(${CMAKE_BINARY_DIR}/ImageProcessingLibrary ${CMAKE_BINARY_DIR}/ImageProcessingLibrary-build)

# Добавляем свои исходные файлы
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

add_library(HeightMapGenerator STATIC ${SOURCES} ${HEADERS})

# Подключение заголовочных файлов
target_include_directories(HeightMapGenerator PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/ImageProcessingLibrary/include>
    $<INSTALL_INTERFACE:include/ImageProcessingLibrary>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/ImageProcessingLibrary/include/third_party>
    $<INSTALL_INTERFACE:include/ImageProcessingLibrary/third_party>
)

# Связывание с ImageProcessingLibrary
target_link_libraries(HeightMapGenerator PRIVATE ImageProcessing)

# Установка библиотеки
install(TARGETS HeightMapGenerator
    EXPORT HeightMapGeneratorTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)
install(EXPORT HeightMapGeneratorTargets DESTINATION cmake)