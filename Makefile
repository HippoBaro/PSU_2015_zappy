##
## Makefile for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy
## 
## Made by Christian Diaconu
## Login   <diacon_c@epitech.net>
## 
## Started on  Sun Jun 12 17:02:15 2016 Christian Diaconu
## Last update Sat Jun 25 12:36:34 2016 Christian Diaconu
##

INC	=	includes/

SRC	=	srcs/Generic.c \
		srcs/Drone/Drone.c \
		srcs/LinkedList/LinkedList.c \
		srcs/LinkedList/LinkedList_add.c \
		srcs/LinkedList/LinkedList_forEach.c \
		srcs/LinkedList/LinkedList_free.c \
		srcs/LinkedList/LinkedList_getElem.c \
		srcs/LinkedList/LinkedList_remove.c \
		srcs/LinkedList/LinkedList_utils.c \
		srcs/Map/maptile_ressources.c \
		srcs/Map/maptile_player_directions.c \
		srcs/Map/maptile_player_sight.c \
		srcs/Map/maptile_players.c \
		srcs/Map/maptile.c \
		srcs/Map/sound.c \
		srcs/Map/map.c \
		srcs/Map/map_sight.c \
		srcs/Request/Request.c \
		srcs/Response/Response.c \
		srcs/Item/Item.c \
		srcs/Request/Parser.c\
		srcs/ZappyServer/ZappyServer.c\
		srcs/ZappyServer/Configuration.c \
		srcs/Request/Timer.c \
		srcs/Network/Network.c \
		srcs/Network/Network_utils.c \
		srcs/Network/Network_client.c \
		srcs/Network/Network_server.c \
		srcs/Network/Network_receive.c \
		srcs/Network/Network_send.c \
		srcs/Team/Team.c

NAME	=	zappy_server

$(NAME):
		gcc srcs/main.c $(SRC) -I $(INC) -o $(NAME)

maptest:
		gcc -g -w unit-tests/sound_main.c $(SRC) -I $(INC) -o "6"
		gcc -g -w unit-tests/drone_directions.c  $(SRC) -I $(INC) -o "5"
		gcc -g -w unit-tests/maptile_ressources.c  $(SRC) -I $(INC) -o "1"
		gcc -g -w unit-tests/maptile_player.c unit-tests/unit-main.c  $(SRC) -I $(INC) -o "2"
		gcc -g -w unit-tests/map.c unit-tests/unit-main.c $(SRC) -I $(INC) -o "3"
		gcc -g -w unit-tests/Drones.c unit-tests/unit-main.c $(SRC) -I $(INC) -o "4"
fclean:		
		rm -rf $(NAME)

clean:

re:		fclean $(NAME)
