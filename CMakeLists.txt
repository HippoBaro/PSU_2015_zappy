cmake_minimum_required(VERSION 2.8)
project(PSU_2015_zappy)

set(CMAKE_C_FLAGS " -g -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-function")

include_directories("includes/")

set(SOURCE_FILES
        srcs/LinkedList/LinkedList.c
        srcs/Network/Network.c
        srcs/Request/Request.c
        srcs/Generic.c
        srcs/Drone/Drone.c
        srcs/Response/Response.c
        srcs/Item/Item.c
        srcs/Map/map.c
        srcs/Map/map_sight.c
        srcs/Map/maptile.c
        srcs/Map/maptile_player_directions.c
        srcs/Map/maptile_player_sight.c
        srcs/Map/maptile_players.c
        srcs/Map/maptile_ressources.c
        srcs/Request/Parser.c
        srcs/ZappyServer/ZappyServer.c
        srcs/ZappyServer/Configuration.c
        srcs/Request/Timer.c

        includes/Map.h
        includes/MapTile.h
        includes/MapSight.h
        includes/Drone.h
        includes/Generic.h
        includes/LinkedList.h
        includes/Network.h
        includes/Request.h
        includes/Response.h
        includes/Item.h
        includes/ZappyServer.h
        includes/Timer.h)

set(UNIT_TEST_SOURCE
        unit-tests/linked_list.c
        unit-tests/Drones.c
        unit-tests/map.c
        unit-tests/maptile_player.c
        unit-tests/main.c)

set(MAIN_SOURCE
        srcs/Network/Network.c
        srcs/main.c
        includes/Sound.h)

#set(UNIT_TEST TRUE)

if (UNIT_TEST)
    add_executable(PSU_2015_zappy ${SOURCE_FILES} ${UNIT_TEST_SOURCE})
else()
    add_executable(PSU_2015_zappy ${SOURCE_FILES} ${MAIN_SOURCE})
endif()


