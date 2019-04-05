# all : main_loop_draft map_creator player_generation

main: main_loop_draft.c player_generator.o map_creator.o data_structures.h
	cc -o main_loop_draft main_loop_draft.c player_generator.o map_creator.o data_structures.h

player_generator.o: player_generator.c data_structures.h
	cc -c player_generator.c

map_creator.o: map_creator.c data_structures.h
	cc -c map_creator.c

clean :
	rm *.o
	rm main_loop_draft


# data_structures.o: data_structures.c
# 	cc -c data_structures.c

# player_generation: player_generator.c
# 	cc -o player_generator player_generator.c
#
# map_creator: map_creator.c
# 	cc -o map_creator map_creator.c
