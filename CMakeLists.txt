PROJECT(lemIPC)

set(sources src/main.c include/lemipc.h src/lemipc.c src/initipc.c src/render/text/render.c src/render/graphical/render.c)

add_executable(lemipc ${sources})