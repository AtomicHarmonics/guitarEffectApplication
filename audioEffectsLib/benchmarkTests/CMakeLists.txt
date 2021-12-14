if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/benchmark)
execute_process (COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/buildScript.sh ${CMAKE_CURRENT_SOURCE_DIR})
endif()
set(audioEffectsLibBenchmark_SRCS
    src/audioEffectsLibBenchmark.cpp
)
add_executable(audioEffectsLibBenchmark
${audioEffectsLibBenchmark_SRCS}
)

include_directories(inc)
add_subdirectory(benchmark)
# Specify here the libraries this program depends on
target_link_libraries(audioEffectsLibBenchmark
benchmark::benchmark
audioEffectsLibSrc
)


install(TARGETS audioEffectsLibBenchmark DESTINATION bin)
