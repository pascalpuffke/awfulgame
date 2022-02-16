cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(Game LANGUAGES CXX)

if(CMAKE_BUILD_TYPE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
endif()

set(CPM_DOWNLOAD_VERSION 0.35.0)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
  message(STATUS "Downloading CPM.cmake v${CPM_DOWNLOAD_VERSION}")
  file(DOWNLOAD https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif()
include(${CPM_DOWNLOAD_LOCATION})

set(SOURCES
    src/main.cpp
    src/util/Benchmarking.cpp
    src/resources/TilesetLoader.cpp
    src/level/Level.cpp
    src/level/LevelLoader.cpp
    src/entity/BaseEntity.cpp
    src/entity/AnimatedEntity.cpp
    src/entity/PlayerEntity.cpp)

CPMAddPackage(
        NAME robin-hood-hashing
        VERSION 3.11.5
        GITHUB_REPOSITORY martinus/robin-hood-hashing
        GIT_TAG 3.11.5
)
CPMAddPackage(
    NAME fmt
    VERSION 8.1.1
    GITHUB_REPOSITORY fmtlib/fmt
    GIT_TAG 8.1.1
)
CPMAddPackage(
    NAME raylib
    VERSION 4.0.0
    GITHUB_REPOSITORY raysan5/raylib
    GIT_TAG 4.0.0
)
CPMAddPackage(
    NAME raylib-cpp
    VERSION 4.1.0
    GITHUB_REPOSITORY robloach/raylib-cpp
    GIT_TAG v4.1.0
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} fmt::fmt raylib raylib_cpp)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS OFF)
