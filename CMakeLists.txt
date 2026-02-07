cmake_minimum_required(VERSION 3.28.3)
project(Avoidance C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

include(FetchContent)

set(RAYLIB_VERSION 5.5)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib
  GIT_TAG ${RAYLIB_VERSION}
)

FetchContent_MakeAvailable(raylib)

add_executable(${PROJECT_NAME} src/main.c src/keys.c src/game.c src/render.c)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
