include(FetchContent)
FetchContent_Declare(
    SDL3Source
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG f686492
    #GIT_SHALLOW 1
)
FetchContent_MakeAvailable(SDL3Source)