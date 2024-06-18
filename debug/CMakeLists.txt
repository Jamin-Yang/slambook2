cmake_minimum_required(VERSION 3.0)

project(main)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Ceres REQUIRED)

include_directories(${CERES_INCLUDE_DIRS})
add_executable(main main.cpp)

target_link_libraries(main ${CERES_LIBRARIES})