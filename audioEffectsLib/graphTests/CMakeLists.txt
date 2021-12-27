set(audioEffectsLibGraphTests_SRCS
    src/audioEffectsGraphTests.cpp
)
add_executable(audioEffectsLibGraphTests
${audioEffectsLibGraphTests_SRCS}
)

include_directories(inc)
# Specify here the libraries this program depends on
target_link_libraries(audioEffectsLibGraphTests
audioEffectsLibSrc
)


install(TARGETS audioEffectsLibGraphTests DESTINATION bin)
