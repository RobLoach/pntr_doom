# PureDOOM
include(FetchContent)
FetchContent_Declare(
    PureDOOM
    GIT_REPOSITORY https://github.com/ammrat13/PureDOOM.git
    GIT_TAG 1f15034aee6f1dfd88f8652788916755440ce1f5
)

FetchContent_Populate(PureDOOM)
add_library(PureDOOM INTERFACE)
target_include_directories(PureDOOM INTERFACE ${puredoom_SOURCE_DIR})


#FetchContent_MakeAvailable(PureDOOM)


#FetchContent_GetProperties(PureDOOM)
#add_library(PureDOOM INTERFACE)
#target_include_directories(PureDOOM INTERFACE ${PureDOOM_SOURCE_DIR})


#FetchContent_GetProperties(PureDOOM)
#if (NOT PureDOOM_POPULATED)
#    set(FETCHCONTENT_QUIET NO)
#    FetchContent_Populate(PureDOOM)
#    
#    add_library(PureDOOM INTERFACE)
#    target_include_directories(PureDOOM INTERFACE ${PureDOOM_SOURCE_DIR})
#endif()
