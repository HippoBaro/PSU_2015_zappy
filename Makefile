##
## Makefile for Makefile in /home/diacon_c/Desktop/PSU_2015_zappy
## 
## Made by Christian Diaconu
## Login   <diacon_c@epitech.net>
## 
## Started on  Mon Jun 27 00:37:38 2016 Christian Diaconu
## Last update Mon Jun 27 02:18:17 2016 Christian Diaconu
##

CC		=	gcc

INCLUDES	=	includes/

CCFLAGS		=	-W 

RM		=	rm -rf

NAME		=	zappy_server

NAME_LIB	=	zappy.so

OBJS		=	$(SRCS:.c=.o)

SRCS		=	srcs/LinkedList/LinkedList.c \
			srcs/LinkedList/LinkedList_add.c \
			srcs/LinkedList/LinkedList_forEach.c \
			srcs/LinkedList/LinkedList_free.c \
			srcs/LinkedList/LinkedList_getElem.c \
			srcs/LinkedList/LinkedList_remove.c \
			srcs/LinkedList/LinkedList_utils.c \
			srcs/Network/Network.c \
			srcs/Network/Network_utils.c \
			srcs/Network/Network_client.c \
			srcs/Network/Network_server.c \
			srcs/Network/Network_receive.c \
			srcs/Network/Network_send.c \
			srcs/Request/Request.c \
			srcs/Generic/Generic.c \
			srcs/Generic/Time.c \
			srcs/Generic/Log.c \
			srcs/Generic/String.c \
			srcs/Drone/Drone.c \
			srcs/Response/Response.c \
			srcs/Item/Item.c \
			srcs/Map/map.c \
			srcs/Map/sound.c \
			srcs/Map/map_sight.c \
			srcs/MapTile/maptile.c \
			srcs/MapTile/maptile_player_directions.c \
			srcs/MapTile/maptile_player_sight.c \
			srcs/MapTile/maptile_players.c \
			srcs/MapTile/maptile_ressources.c \
			srcs/Request/Parser.c \
			srcs/ZappyServer/ZappyServer.c \
			srcs/ZappyServer/Configuration.c \
			srcs/ZappyServer/Request.c \
			srcs/ZappyServer/Drone.c \
			srcs/ZappyServer/LifeCycle.c \
			srcs/Request/Timer.c \
			srcs/Request/Transaction.c \
			srcs/Team/Team.c \
			srcs/Drone/Action/Move.c \
			srcs/Drone/Action/Inventory.c \
			srcs/Drone/Action/Map.c \
			srcs/Drone/Request.c \
			srcs/Drone/Action/Team.c \
			srcs/Drone/Action/Incant.c \
			srcs/Map/sound_getnum.c \
			srcs/Drone/Validation/Inventory.c \
			srcs/Drone/Validation/Move.c \
			srcs/Drone/Validation/Map.c \
			srcs/Drone/Validation/Incant.c \
			srcs/Map/Seed.c \
			srcs/Map/Drone.c

all:			$(NAME) $(NAME_LIB)

$(NAME):
			$(CC) -o $(NAME) $(CCFLAGS) -I $(INCLUDES) $(SRCS) srcs/main.c

$(NAME_LIB):
			$(CC) -shared -o $(NAME_LIB) -fPIC $(SRCS) -I $(INCLUDES)

clean:
			$(RM) *~ *# *.o

fclean:			clean
			$(RM) $(NAME)
			$(RM) $(NAME_LIB)

re:			fclean all
