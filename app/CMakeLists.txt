
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(Main_SRCS
    src/main.cpp
)

add_executable(effectsApp
${Main_SRCS}
)

include_directories(inc)

# Specify here the libraries this program depends on
target_link_libraries(effectsApp
audioEffectsLibSrc
)
find_package(PkgConfig)
if (PKG_CONFIG_FOUND)
  pkg_check_modules(JACK "jack")
  if (JACK_FOUND)    
    target_link_libraries(effectsApp ${JACK_LIBRARIES})
    add_definitions(${JACK_CFLAGS} ${JACK_CFLAGS_OTHER})
  endif()
endif()


install(TARGETS effectsApp DESTINATION bin)
