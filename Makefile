objects = main.o player_generator.o map_creator.o print_map.o place_penguins.o placement_legality_check.o update_map.o

penguins : $(objects)
	cc -o penguins $(objects)

main.o : player_generator.h map_creator.h place_penguins.h data_structures.h
player_generator.o : data_structures.h
map_creator.o : data_structures.h
print_map.o : data_structures.h
place_penguins.o : placement_legality_check.h update_map.h data_structures.h
placement_legality_check.o : data_structures.h
update_map.o : data_structures.h

.PHONY : clean
clean :
	rm penguins $(objects)

# data_structures.o: data_structures.c
# 	cc -c data_structures.c

# player_generation: player_generator.c
# 	cc -o player_generator player_generator.c
#
# map_creator: map_creator.c
# 	cc -o map_creator map_creator.c
