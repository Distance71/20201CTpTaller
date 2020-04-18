cmake_minimum_required(VERSION 3.10.2)
project(game)
set(CMAKE_CXX_STANDARD 17)

#Bring the headers, such as Student.h into the project
include_directories(src/*)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/vendor/cmake-sl2-image/)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

file(GLOB GeneralSources "src/game/*.cpp")
file(GLOB ProvidersSources src/providers/*.cpp)
file(GLOB ServicesSources src/services/*.cpp)

add_executable(game ${GeneralSources} ${ProvidersSources} ${ServicesSources})
target_link_libraries(game ${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY})