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
        GIT_TAG "99b0707988a581ca807c46e3ca686fa458eada01"
        GIT_PROGRESS TRUE
    )

    FetchContent_MakeAvailable(raylib)
endif()

set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(PROJECT_SOURCES
    src/audio.c
    src/bubble.c
    src/enemy.c
    src/game.c
    src/input.c
    src/level.c
    src/main.c
    src/menu.c
    src/paths.c
    src/player.c
    src/projectile.c
    src/render.c
    src/save.c
    src/stage1_library.c
    src/stage1_library_render.c
)

add_executable(CMSC11-Machine-Problem ${PROJECT_SOURCES})

target_include_directories(CMSC11-Machine-Problem PRIVATE ${PROJECT_INCLUDE_DIR})
target_link_libraries(CMSC11-Machine-Problem PRIVATE raylib)

target_compile_definitions(CMSC11-Machine-Problem PRIVATE
    PLATFORM_DESKTOP
    ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Assets/"
    LEVELS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/levels/"
)

install(TARGETS CMSC11-Machine-Problem RUNTIME DESTINATION .)
install(DIRECTORY Assets levels DESTINATION .)

message(STATUS "Configured ${PROJECT_NAME} with raylib support.")

