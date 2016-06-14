##
## Makefile for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy
## 
## Made by Christian Diaconu
## Login   <diacon_c@epitech.net>
## 
## Started on  Sun Jun 12 17:02:15 2016 Christian Diaconu
## Last update Mon Jun 13 21:02:08 2016 Christian Diaconu
##

INC	=	includes/

SRC	=	srcs/Generic.c \
		srcs/Drone/Drone.c \
		srcs/LinkedList/LinkedList.c \
		srcs/Map/maptile_ressources.c \
		srcs/Map/maptile_players.c \
		srcs/Map/maptile.c \
		srcs/Map/map.c \
		srcs/Map/map_sight.c \
		srcs/Request/Request.c \
		srcs/Response/Response.c \
		srcs/Item/Item.c

NAME	=	zappy_server

$(NAME):
		gcc srcs/main.c $(SRC) -I $(INC) -o $(NAME)

maptest:
		gcc -g -w unit-tests/maptile_ressources.c  $(SRC) -I $(INC) -o "1"
		gcc -g -w unit-tests/maptile_player.c  $(SRC) -I $(INC) -o "2"
		gcc -g -w unit-tests/map.c  $(SRC) -I $(INC) -o "3"

fclean:		
		rm -rf $(NAME)

clean:

re:		fclean $(NAME)
