#!/bin/sh

x86_64-w64-mingw32-gcc src/*.c -o Avoidance2.exe -L../raylib/src -I../raylib/src -Isrc -l:libraylib.a -lopengl32 -lgdi32 -lwinmm
