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

add_executable(pntr_doom
    pntr_doom.c
)
target_compile_definitions(pntr_doom PUBLIC PNTR_APP_SDL)

# SDL
find_package(SDL2 QUIET)
if(SDL2_FOUND)
    message(STATUS "Using SDL2 via find_package")
endif()
if(NOT SDL2_FOUND)
    include(FetchContent)
    set(SDL_SHARED TRUE CACHE BOOL "Build a SDL shared library (if available)")
    set(SDL_STATIC TRUE CACHE BOOL "Build a SDL static library (if available)")
    FetchContent_Declare(
        SDL
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.30.1  # Replace this with a particular git tag or git hash
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
    )
    message(STATUS "Using SDL2 via FetchContent")
    FetchContent_MakeAvailable(SDL)
    set_property(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/_deps/sdl-src" PROPERTY EXCLUDE_FROM_ALL TRUE)
endif()

# Link
target_link_libraries(pntr_doom PRIVATE
    pntr
    pntr_app
    SDL2::SDL2-static
)

# Include Directories
target_include_directories(pntr_doom PUBLIC vendor/PureDOOM)

set_property(TARGET pntr_doom PROPERTY C_STANDARD 11)
