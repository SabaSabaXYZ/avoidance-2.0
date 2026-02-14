cmake_minimum_required(VERSION 3.28.3)
project(Avoidance2 C)

if (EMSCRIPTEN)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()

set(CMAKE_BUILD_TYPE RELEASE)
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

find_library(MATH_LIB m)
if (MATH_LIB)
  target_link_libraries(${PROJECT_NAME} PRIVATE ${MATH_LIB})
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
