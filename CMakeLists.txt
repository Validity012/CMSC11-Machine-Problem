cmake_minimum_required(VERSION 3.14)

project(CMSC11_Machine_Problem LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use a system-installed raylib when available. Otherwise fetch a compatible release.
find_package(raylib QUIET)
if(NOT raylib_FOUND)
    include(FetchContent)

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_WAYLAND ON CACHE BOOL "" FORCE)
    set(GLFW_BUILD_X11 OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
        raylib
        GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
        GIT_TAG "master"
        GIT_PROGRESS TRUE
    )

    FetchContent_MakeAvailable(raylib)
endif()

set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Keep src/player.c as the active entry point for now; the repo still has a placeholder main there.
# Once a real main is added to src/main.c, move the entry point there and remove the placeholder.
set(PROJECT_SOURCES
    src/audio.c
    src/bubble.c
    src/enemy.c
    src/game.c
    src/input.c
    src/level.c
    src/player.c
    src/projectile.c
    src/render.c
    src/save.c
)

add_executable(CMSC11-Machine-Problem ${PROJECT_SOURCES})

target_include_directories(CMSC11-Machine-Problem PRIVATE ${PROJECT_INCLUDE_DIR})
target_link_libraries(CMSC11-Machine-Problem PRIVATE raylib)

target_compile_definitions(CMSC11-Machine-Problem PRIVATE
    PLATFORM_DESKTOP
    ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Assets/"
    LEVELS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/levels/"
)

message(STATUS "Configured ${PROJECT_NAME} with raylib support.")"

