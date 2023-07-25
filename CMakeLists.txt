cmake_minimum_required(VERSION 3.11)
project(pntr
    DESCRIPTION "pntr_doom: Doom for pntr"
    HOMEPAGE_URL "https://github.com/robloach/pntr_doom"
    VERSION 0.0.1
    LANGUAGES C
)

# Options
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    set(PNTR_DOOM_IS_MAIN TRUE)
else()
    set(PNTR_DOOM_IS_MAIN FALSE)
endif()
option(PNTR_DOOM_BUILD_RAYLIB "raylib" ${PNTR_DOOM_IS_MAIN})

# CMAKE Modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(pntr)
find_package(pntr_app)
find_package(PureDOOM)

if (EMSCRIPTEN)
    add_executable(pntr_doom_emscripten
        pntr_doom.c
    )
    target_link_libraries(pntr_doom_emscripten PUBLIC
        pntr
        pntr_app
        PureDOOM
    )

    set_target_properties(pntr_doom_emscripten PROPERTIES PREFIX "")
    set_target_properties(pntr_doom_emscripten PROPERTIES SUFFIX ".html")
    set_target_properties(pntr_doom_emscripten PROPERTIES OUTPUT_NAME "index")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --preload-file resources@/resources --shell-file ${CMAKE_SOURCE_DIR}/pntr_doom.html")

    # Disable the other runtimes
    set(PNTR_DOOM_BUILD_RAYLIB FALSE)
endif()

if (PNTR_DOOM_BUILD_RAYLIB)
    find_package(raylib)
    add_executable(pntr_doom_raylib pntr_doom.c)
    target_link_libraries(pntr_doom_raylib PUBLIC
        pntr
        pntr_app
        PureDOOM
        raylib
    )
    target_compile_definitions(pntr_doom_raylib PUBLIC PNTR_APP_RAYLIB)
endif()