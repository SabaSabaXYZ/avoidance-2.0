#!/bin/sh

emcc src/*.c -O3 -o index.html -L../raylib/src -I../raylib/src -l:libraylib.web.a -s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 -s ALLOW_MEMORY_GROWTH=1 -DTARGET_WEB
