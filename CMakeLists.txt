PROJECT(lemIPC)

set(CMAKE_EXE_LINKER_FLAGS "-lc_graph_prog -lpthread")

set(sources
        src/main.c
        include/lemipc.h
        src/lemipc.c
        src/initipc.c
        src/render/text/render.c
        src/render/graphical/render.c
        src/render/graphical/graph_functions.c
        src/render/color/color_generator.c
        include/color.h
        src/render/color/handle_color_list.c
        src/render/graphical/print_map.c
        src/player/player.c src/player/utility.c src/player/player_move.c src/utility.c src/messages/handle.c src/messages/my_str_to_wordtab.c src/commander/commander.c src/commander/snail_research.c src/commander/commander_functions.c src/player/commander_relieving.c src/game/determine_winner.c src/game/winner_functions.c)

add_executable(lemipc ${sources})