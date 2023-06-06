cmake_minimum_required(VERSION 3.0.0)
project(basicRandomWalk VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
add_executable(basicRandomWalk main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(${PROJECT_NAME} SDL2)
