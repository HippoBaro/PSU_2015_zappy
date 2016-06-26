cmake_minimum_required(VERSION 2.8)
project(PSU_2015_zappy)

set(CMAKE_C_FLAGS " -g -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-function")

include_directories("includes/")

set(SOURCE_FILES
        srcs/LinkedList/LinkedList.c
        srcs/LinkedList/LinkedList_add.c
        srcs/LinkedList/LinkedList_forEach.c
        srcs/LinkedList/LinkedList_free.c
        srcs/LinkedList/LinkedList_getElem.c
        srcs/LinkedList/LinkedList_remove.c
        srcs/LinkedList/LinkedList_utils.c
        srcs/Network/Network.c
        srcs/Network/Network_utils.c
        srcs/Network/Network_client.c
        srcs/Network/Network_server.c
        srcs/Network/Network_receive.c
        srcs/Network/Network_send.c
        srcs/Request/Request.c
        srcs/Generic/Generic.c
        srcs/Drone/Drone.c
        srcs/Response/Response.c
        srcs/Item/Item.c
        srcs/Map/map.c
        srcs/Map/sound.c
        srcs/Map/map_sight.c
        srcs/MapTile/maptile.c
        srcs/MapTile/maptile_player_directions.c
        srcs/MapTile/maptile_player_sight.c
        srcs/MapTile/maptile_players.c
        srcs/MapTile/maptile_ressources.c
        srcs/Request/Parser.c
        srcs/ZappyServer/ZappyServer.c
        srcs/ZappyServer/Configuration.c
        srcs/Request/Timer.c
        srcs/Team/Team.c
        srcs/Drone/Action/Move.c
        srcs/Drone/Action/Inventory.c
        srcs/Drone/Action/Map.c
        srcs/Drone/Request.c
        srcs/Drone/Action/Team.c
        srcs/Drone/Action/Incant.c
        srcs/Map/sound_getnum.c
        srcs/Drone/Validation/Inventory.c
        srcs/Drone/Validation/Move.c
        srcs/Drone/Validation/Map.c
        srcs/Drone/Validation/Incant.c
        srcs/Map/Seed.c
        srcs/Map/Drone.c
        srcs/Network/Network.c

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
        includes/Timer.h
        includes/Sound.h
        includes/Team.h)

set(UNIT_TEST_SOURCE
        unit-tests/linked_list.c
        unit-tests/Drones.c
        unit-tests/map.c
        unit-tests/maptile_player.c
        unit-tests/main.c)

set(MAIN_SOURCE srcs/main.c
        srcs/Request/Transaction.c
        srcs/ZappyServer/Request.c
        srcs/ZappyServer/Drone.c
        srcs/ZappyServer/LifeCycle.c
        srcs/Generic/Log.c
        srcs/Generic/String.c)

#set(UNIT_TEST TRUE)

if (UNIT_TEST)
    add_executable(PSU_2015_zappy ${SOURCE_FILES} ${UNIT_TEST_SOURCE})
else()
    add_executable(PSU_2015_zappy ${SOURCE_FILES} ${MAIN_SOURCE})
endif()


