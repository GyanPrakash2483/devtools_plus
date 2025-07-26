cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_COMPILER clang++)

project(devtools_plus CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
    endstone
    GIT_REPOSITORY https://github.com/EndstoneMC/endstone.git
    GIT_TAG "v0.9.4"
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(endstone)

endstone_add_plugin(${PROJECT_NAME}
    src/devtools_plus.cpp
    src/util.cpp
    src/genplugin.cpp
    src/buildplugin.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE include)