cmake_minimum_required(VERSION 3.5)
project(PSU_2015_zappy)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

include_directories("includes/")

set(SOURCE_FILES
        unit-tests/map.c
        #srcs/main.c
        srcs/LinkedList/LinkedList.c
        #srcs/Network/Network.c
        srcs/Request/Request.c
        srcs/Generic.c
        srcs/Drone/Drone.c
        srcs/Response/Response.c
        srcs/Item/Item.c
        srcs/Map/map.c
        srcs/Map/maptile.c

        includes/Drone.h
        includes/Generic.h
        includes/LinkedList.h
        includes/Network.h
        includes/Request.h
        includes/Response.h
        includes/Item.h)

add_executable(PSU_2015_zappy ${SOURCE_FILES})
