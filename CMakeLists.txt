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
option(PNTR_DOOM_BUILD_SDL "SDL" ${PNTR_DOOM_IS_MAIN})

# CMAKE Modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(pntr)
find_package(pntr_app)

# SDL
if (PNTR_DOOM_BUILD_SDL)
    find_package(SDL2 QUIET)
    
    # SDL_mixer
    set(SDLMIXER_BUILD_SHARED_LIBS false)
    set(SDLMIXER_VORBIS STB)
    set(SDLMIXER_INSTALL OFF)
    set(SDLMIXER_DEPS_SHARED OFF)
    set(SDLMIXER_VENDORED OFF)
    set(SDLMIXER_SAMPLES OFF)
    set(SDLMIXER_CMD OFF)
    set(SDLMIXER_FLAC OFF)
    set(SDLMIXER_MOD OFF)
    set(SDLMIXER_MP3 OFF)
    set(SDLMIXER_MIDI_NATIVE OFF)
    set(SDLMIXER_OPUS OFF)
    set(SDLMIXER_OPUS_SHARED OFF)
    set(SDLMIXER_MIDI_FLUIDSYNTH OFF)
    set(SDLMIXER_MP3_MPG123 OFF)
    set(SDLMIXER_MP3_DRMP3 OFF)
    set(SDLMIXER_MOD_XMP OFF)
    set(SDLMIXER_MOD_MODPLUG OFF)
    set(SDLMIXER_FLAC_DRFLAC OFF)
    set(SDLMIXER_FLAC_LIBFLAC OFF)
    set(SDLMIXER_VORBIS_VORBISFILE OFF)
    set(SDLMIXER_WAVPACK OFF)
    set(SDLMIXER_SAMPLES_INSTALL OFF)
    set(SDLMIXER_BUILD_SHARED_LIBS OFF)
    find_package(SDL3_mixer REQUIRED)
endif()

# raylib
if (PNTR_DOOM_BUILD_RAYLIB)
    find_package(raylib QUIET)
endif()

if (PNTR_DOOM_BUILD_SDL)
    add_executable(pntr_doom_sdl
        pntr_doom.c
    )
    target_compile_definitions(pntr_doom_sdl PUBLIC 
        PNTR_APP_SDL
        PNTR_PIXELFORMAT_ARGB
    )
    target_link_libraries(pntr_doom_sdl PRIVATE
        pntr
        pntr_app
        SDL3::SDL3-static
        SDL3_mixer::SDL3_mixer-static
    )
    target_include_directories(pntr_doom_sdl PUBLIC vendor/PureDOOM)
    set_property(TARGET pntr_doom_sdl PROPERTY C_STANDARD 11)
endif()

if (PNTR_DOOM_BUILD_RAYLIB)
    add_executable(pntr_doom_raylib
        pntr_doom.c
    )
    target_compile_definitions(pntr_doom_raylib PUBLIC PNTR_APP_RAYLIB)
    target_link_libraries(pntr_doom_raylib PRIVATE
        pntr
        pntr_app
        raylib_static
    )
    target_include_directories(pntr_doom_raylib PUBLIC vendor/PureDOOM)
    set_property(TARGET pntr_doom_raylib PROPERTY C_STANDARD 11)
endif()