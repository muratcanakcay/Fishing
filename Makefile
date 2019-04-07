# all : main map_creator player_generation

main: main.c player_generator.o map_creator.o print_map.o data_structures.h
	cc -o penguins main.c player_generator.o map_creator.o print_map.o data_structures.h

player_generator.o: player_generator.c data_structures.h
	cc -c player_generator.c

map_creator.o: map_creator.c data_structures.h
	cc -c map_creator.c

print_map.o: print_map.c data_structures.h
	cc -c print_map.c

clean :
	rm *.o
	rm penguins

# data_structures.o: data_structures.c
# 	cc -c data_structures.c

# player_generation: player_generator.c
# 	cc -o player_generator player_generator.c
#
# map_creator: map_creator.c
# 	cc -o map_creator map_creator.c
