cmake_minimum_required(VERSION 3.14)
project(audioEffectsLib)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)


###############
### Testing ###
###############

enable_testing()
add_subdirectory(tests)
add_subdirectory(benchmarkTests)
