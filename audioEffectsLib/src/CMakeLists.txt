set(audioEffectsLibSrc_SOURCE_FILES audioEffects.cpp)

include_directories(../inc)


add_library(audioEffectsLibSrc STATIC ${audioEffectsLibSrc_SOURCE_FILES})

target_link_libraries(audioEffectsLibSrc
ssl
crypto
)

# Specify the include directories exported by this library
target_include_directories(audioEffectsLibSrc PUBLIC ../inc)
