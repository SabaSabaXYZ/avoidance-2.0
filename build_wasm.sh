#!/bin/sh

# emcmake cmake -DCMAKE_TOOLCHAIN_FILE=../../emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -DPLATFORM=Web -B .
emcc src/*.c -o Avoidance2.html -L../raylib/src -I../raylib/src -l:libraylib.web.a -s USE_GLFW=3 -s ASYNCIFY -s STACK_SIZE=67108864
