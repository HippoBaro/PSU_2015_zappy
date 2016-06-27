cmake_minimum_required(VERSION 2.8)
project(PSU_2015_zappy)

set(CMAKE_C_FLAGS " -g -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-function")

include_directories("includes/")

set(SOURCE_FILES
        srcs/Drone/Action/Incant.c
        srcs/Drone/Action/Inventory.c
        srcs/Drone/Action/Map.c
        srcs/Drone/Action/Move.c
        srcs/Drone/Action/Team.c
        srcs/Drone/Validation/Incant.c
        srcs/Drone/Validation/Inventory.c
        srcs/Drone/Validation/Map.c
        srcs/Drone/Validation/Move.c
        srcs/Drone/Drone.c
        srcs/Drone/Request.c
        srcs/Generic/Generic.c
        srcs/Generic/Log.c
        srcs/Generic/String.c
        srcs/Generic/Time.c
        srcs/Item/Item.c
        srcs/LinkedList/LinkedList.c
        srcs/LinkedList/LinkedList_add.c
        srcs/LinkedList/LinkedList_forEach.c
        srcs/LinkedList/LinkedList_free.c
        srcs/LinkedList/LinkedList_getElem.c
        srcs/LinkedList/LinkedList_remove.c
        srcs/LinkedList/LinkedList_utils.c
        srcs/Map/Drone.c
        srcs/Map/map.c
        srcs/Map/map_sight.c
        srcs/Map/Seed.c
        srcs/Map/sound.c
        srcs/Map/sound_getnum.c
        srcs/MapTile/maptile.c
        srcs/MapTile/maptile_player_directions.c
        srcs/MapTile/maptile_player_sight.c
        srcs/MapTile/maptile_players.c
        srcs/MapTile/maptile_ressources.c
        srcs/Network/Network.c
        srcs/Network/Network_client.c
        srcs/Network/Network_receive.c
        srcs/Network/Network_send.c
        srcs/Network/Network_server.c
        srcs/Network/Network_utils.c
        srcs/Request/Parser.c
        srcs/Request/Request.c
        srcs/Request/Timer.c
        srcs/Request/Transaction.c
        srcs/Response/Response.c
        srcs/Team/Team.c
        srcs/ZappyServer/Configuration.c
        srcs/ZappyServer/Drone.c
        srcs/ZappyServer/LifeCycle.c
        srcs/ZappyServer/Request.c
        srcs/ZappyServer/ZappyServer.c
        GraphClient/blitRess.c
        GraphClient/blitRess_next.c
        GraphClient/command.c
        GraphClient/graph.c
        GraphClient/terrain.c
        GraphClient/utils.c




        includes/Drone.h
        includes/Generic.h
        includes/GraphClient.h
        includes/Item.h
        includes/LinkedList.h
        includes/Map.h
        includes/MapSight.h
        includes/MapTile.h
        includes/Network.h
        includes/Request.h
        includes/Response.h
        includes/Sound.h
        includes/Team.h
        includes/Timer.h
        includes/ZappyServer.h
        )

set(MAIN_SOURCE
        GraphClient/clientGraph.c
        #srcs/main.c
        )

add_executable(PSU_2015_zappy ${SOURCE_FILES} ${MAIN_SOURCE})
target_link_libraries(PSU_2015_zappy SDL SDL_image)


