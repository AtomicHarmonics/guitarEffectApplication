set(audioEffectsLibGraphTests_SRCS
    src/audioEffectsLibGraphTests.cpp
)
add_executable(audioEffectsLibGraphTests
${audioEffectsLibGraphTests_SRCS}
)

include_directories(inc)
include_directories(/usr/include/python3.8)
# Specify here the libraries this program depends on
target_link_libraries(audioEffectsLibGraphTests
audioEffectsLibSrc
python3.8
)


install(TARGETS audioEffectsLibGraphTests DESTINATION bin)
