#!/bin/sh

emcc src/*.c -o index.html -L../raylib/src -I../raylib/src -l:libraylib.web.a -s USE_GLFW=3 -s ASYNCIFY -s STACK_SIZE=67108864
