cmake_minimum_required(VERSION 3.24)
project(undermylife)

set(CMAKE_CXX_STANDARD 23)
set(EXECUTABLE_OUTPUT_PATH ../build/)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
include_directories(src)
add_compile_options(-O3)

add_executable(undermylife ${SRC_FILES})
target_link_options(undermylife PRIVATE -mwindows)
target_link_libraries(undermylife mingw32 opengl32 glew32 SDL2main SDL2)