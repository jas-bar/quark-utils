project(quark_utils)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

add_library(${PROJECT_NAME} STATIC ${SRC_LIST})

# include directories
set(INC_DIRS "")
# libraries
set(LIBS "")

# search for SDL
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_MIXER REQUIRED SDL2_mixer)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)
pkg_search_module(QUARK REQUIRED quark)
pkg_search_module(OPENGL REQUIRED gl glesv2)
set(LIBS ${LIBS} ${SDL2_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${QUARK_LIBRARIES} ${OPENGL_LIBRARIES})
set(INC_DIRS ${INC_DIRS} ${SDL2_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${QUARK_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})

# if there's possibility to add SDLMain, do it...
if(SDLMAIN_LIBRARY)
    set(LIBS ${LIBS} ${SDLMAIN_LIBRARY})
endif(SDLMAIN_LIBRARY)

include_directories(${INC_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIBS})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
file(GLOB HEADERS . "*.h")
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/quark_utils)

configure_file(quark_utils.pc.in ../quark_utils.pc)
install(FILES quark_utils.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig/)
