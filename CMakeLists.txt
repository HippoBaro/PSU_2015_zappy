cmake_minimum_required(VERSION 3.5)
project(PSU_2015_zappy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include_directories("includes")

set(SOURCE_FILES
        srcs/LinkedList/LinkedList.c
        srcs/main.c
        srcs/Request/Request.c
        srcs/Generic.c srcs/Drone/Drone.c includes/Drone.h includes/Response.h srcs/Response/Response.c)

add_executable(PSU_2015_zappy ${SOURCE_FILES})