PROJECT(lemIPC)

set(sources src/main.c include/lemipc.h src/lemipc.c src/initipc.c src/render/text/render.c src/render/graphical/render.c src/render/graphical/graph_functions.c src/render/color/color_generator.c include/color.h src/render/color/handle_color_list.c src/render/graphical/print_map.c)

add_executable(lemipc ${sources})