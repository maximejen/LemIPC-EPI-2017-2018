PROJECT(lemIPC)

set(sources main.c include/lemipc.h lemipc.c initipc.c render/text/render.c render/graphical/render.c)

add_executable(lemipc ${sources})