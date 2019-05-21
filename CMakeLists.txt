cmake_minimum_required(VERSION 3.14)
project(FishingGithub C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(FishingGithub
        choose_penguin.c
        choose_penguin.h
        data_structures.h
        destination_legality_check.c
        destination_legality_check.h
        floe_availability_check.c
        floe_availability_check.h
        get_destination_coordinates.c
        get_destination_coordinates.h
        get_penguin_coordinates.c
        get_penguin_coordinates.h
        get_placement_coordinates.c
        get_placement_coordinates.h
        main.c
        map_generator.c
        map_generator.h
        move_penguins.c
        move_penguins.h
        movement_possibility_check.c
        movement_possibility_check.h
        neighbour_score_check.c
        neighbour_score_check.h
        place_penguins.c
        place_penguins.h
        placement_legality_check.c
        placement_legality_check.h
        player_generator.c
        player_generator.h
        print_map.c
        print_map.h
        update_map.c
        update_map.h
        placement_score_check.c
        placement_score_check.h
        opening_score_check.c
        opening_score_check.h
        )
