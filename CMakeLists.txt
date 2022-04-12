cmake_minimum_required(VERSION 3.20)

project(SimpleChat VERSION 0.1 LANGUAGES CXX )
set(CMAKE_CXX_STANDARD 17)
add_COMPILE_OPTIONS(-Wall -Werror -Wpedantic)

add_subdirectory(src src)
add_subdirectory(ftxui ftxui)

set(FTXUI_BUILD_EXAMPLES OFF)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE window client server connection dom screen component)
