##
## Makefile for zappy in /home/pasteu_e/rendu/PSU_2015_zappy
## 
## Made by Etienne Pasteur
## Login   <pasteu_e@epitech.net>
## 
## Started on  Mon Jun 27 03:02:48 2016 Etienne Pasteur
## Last update Mon Jun 27 04:02:43 2016 Etienne Pasteur
##

CC		=	gcc

INCLUDES	=	./includes/

CFLAGS		=	-I $(INCLUDES) -g -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-function

RM		=	rm -rf

NAME		=	zappy_server

NAME_IA		=	zappy_ia

NAME_GRAPH	=	zappy_graph

NAME_LIB	=	zappy.so

SRCS_SERVER	=	srcs/Drone/Action/Incant.c \
			srcs/Drone/Action/Inventory.c \
			srcs/Drone/Action/Map.c \
			srcs/Drone/Action/Move.c \
			srcs/Drone/Action/Team.c \
			srcs/Drone/Validation/Incant.c \
			srcs/Drone/Validation/Inventory.c \
			srcs/Drone/Validation/Map.c \
			srcs/Drone/Validation/Move.c \
			srcs/Drone/Drone.c \
			srcs/Drone/Request.c \
			srcs/Generic/Generic.c \
			srcs/Generic/Log.c \
			srcs/Generic/String.c \
			srcs/Generic/Time.c \
			srcs/Item/Item.c \
			srcs/LinkedList/LinkedList.c \
			srcs/LinkedList/LinkedList_add.c \
			srcs/LinkedList/LinkedList_forEach.c \
			srcs/LinkedList/LinkedList_free.c \
			srcs/LinkedList/LinkedList_getElem.c \
			srcs/LinkedList/LinkedList_remove.c \
			srcs/LinkedList/LinkedList_utils.c \
			srcs/Map/Drone.c \
			srcs/Map/map.c \
			srcs/Map/map_sight.c \
			srcs/Map/Seed.c \
			srcs/Map/sound.c \
			srcs/Map/sound_getnum.c \
			srcs/MapTile/maptile.c \
			srcs/MapTile/maptile_player_directions.c \
			srcs/MapTile/maptile_player_sight.c \
			srcs/MapTile/maptile_players.c \
			srcs/MapTile/maptile_ressources.c \
			srcs/Network/Network.c \
			srcs/Network/Network_client.c \
			srcs/Network/Network_receive.c \
			srcs/Network/Network_send.c \
			srcs/Network/Network_server.c \
			srcs/Network/Network_utils.c \
			srcs/Request/Parser.c \
			srcs/Request/Request.c \
			srcs/Request/Timer.c \
			srcs/Request/Transaction.c \
			srcs/Response/Response.c \
			srcs/Team/Team.c \
			srcs/ZappyServer/Configuration.c \
			srcs/ZappyServer/Drone.c \
			srcs/ZappyServer/LifeCycle.c \
			srcs/ZappyServer/Request.c \
			srcs/ZappyServer/ZappyServer.c \
			srcs/main.c

SRCS_SO		=	srcs/Drone/Action/Incant.c \
			srcs/Drone/Action/Inventory.c \
			srcs/Drone/Action/Map.c \
			srcs/Drone/Action/Move.c \
			srcs/Drone/Action/Team.c \
			srcs/Drone/Validation/Incant.c \
			srcs/Drone/Validation/Inventory.c \
			srcs/Drone/Validation/Map.c \
			srcs/Drone/Validation/Move.c \
			srcs/Drone/Drone.c \
			srcs/Drone/Request.c \
			srcs/Generic/Generic.c \
			srcs/Generic/Log_so.c \
			srcs/Generic/String.c \
			srcs/Generic/Time.c \
			srcs/Item/Item.c \
			srcs/LinkedList/LinkedList.c \
			srcs/LinkedList/LinkedList_add.c \
			srcs/LinkedList/LinkedList_forEach.c \
			srcs/LinkedList/LinkedList_free.c \
			srcs/LinkedList/LinkedList_getElem.c \
			srcs/LinkedList/LinkedList_remove.c \
			srcs/LinkedList/LinkedList_utils.c \
			srcs/Map/Drone.c \
			srcs/Map/map.c \
			srcs/Map/map_sight.c \
			srcs/Map/Seed.c \
			srcs/Map/sound.c \
			srcs/Map/sound_getnum.c \
			srcs/MapTile/maptile.c \
			srcs/MapTile/maptile_player_directions.c \
			srcs/MapTile/maptile_player_sight.c \
			srcs/MapTile/maptile_players.c \
			srcs/MapTile/maptile_ressources.c \
			srcs/Network/Network.c \
			srcs/Network/Network_client.c \
			srcs/Network/Network_receive.c \
			srcs/Network/Network_send.c \
			srcs/Network/Network_server.c \
			srcs/Network/Network_utils.c \
			srcs/Request/Parser.c \
			srcs/Request/Request.c \
			srcs/Request/Timer.c \
			srcs/Request/Transaction.c \
			srcs/Response/Response.c \
			srcs/Team/Team.c \
			srcs/ZappyServer/Configuration.c \
			srcs/ZappyServer/Drone.c \
			srcs/ZappyServer/LifeCycle.c \
			srcs/ZappyServer/Request.c \
			srcs/ZappyServer/ZappyServer.c

SRCS_GRAPH	=	srcs/Drone/Action/Incant.c \
			srcs/Drone/Action/Inventory.c \
			srcs/Drone/Action/Map.c \
			srcs/Drone/Action/Move.c \
			srcs/Drone/Action/Team.c \
			srcs/Drone/Validation/Incant.c \
			srcs/Drone/Validation/Inventory.c \
			srcs/Drone/Validation/Map.c \
			srcs/Drone/Validation/Move.c \
			srcs/Drone/Drone.c \
			srcs/Drone/Request.c \
			srcs/Generic/Generic.c \
			srcs/Generic/Log.c \
			srcs/Generic/String.c \
			srcs/Generic/Time.c \
			srcs/Item/Item.c \
			srcs/LinkedList/LinkedList.c \
			srcs/LinkedList/LinkedList_add.c \
			srcs/LinkedList/LinkedList_forEach.c \
			srcs/LinkedList/LinkedList_free.c \
			srcs/LinkedList/LinkedList_getElem.c \
			srcs/LinkedList/LinkedList_remove.c \
			srcs/LinkedList/LinkedList_utils.c \
			srcs/Map/Drone.c \
			srcs/Map/map.c \
			srcs/Map/map_sight.c \
			srcs/Map/Seed.c \
			srcs/Map/sound.c \
			srcs/Map/sound_getnum.c \
			srcs/MapTile/maptile.c \
			srcs/MapTile/maptile_player_directions.c \
			srcs/MapTile/maptile_player_sight.c \
			srcs/MapTile/maptile_players.c \
			srcs/MapTile/maptile_ressources.c \
			srcs/Network/Network.c \
			srcs/Network/Network_client.c \
			srcs/Network/Network_receive.c \
			srcs/Network/Network_send.c \
			srcs/Network/Network_server.c \
			srcs/Network/Network_utils.c \
			srcs/Request/Parser.c \
			srcs/Request/Request.c \
			srcs/Request/Timer.c \
			srcs/Request/Transaction.c \
			srcs/Response/Response.c \
			srcs/Team/Team.c \
			srcs/ZappyServer/Configuration.c \
			srcs/ZappyServer/Drone.c \
			srcs/ZappyServer/LifeCycle.c \
			srcs/ZappyServer/Request.c \
			srcs/ZappyServer/ZappyServer.c \
			GraphClient/blitRess.c \
			GraphClient/blitRess_next.c \
			GraphClient/command.c \
			GraphClient/graph.c \
			GraphClient/terrain.c \
			GraphClient/utils.c \
			GraphClient/clientGraph.c

OBJS_SERVER	=	$(SRCS_SERVER:.c=.o)

OBJS_GRAPH	=	$(SRCS_GRAPH:.c=.o)

all:			$(NAME) $(NAME_IA) $(NAME_GRAPH) $(NAME_LIB)

$(NAME):		$(OBJS_SERVER)
			$(CC) $(OBJS_SERVER) -o $(NAME)

$(NAME_IA):		$(NAME_LIB)
			cp Client.exe $(NAME_IA)

$(NAME_GRAPH):		$(OBJS_GRAPH)
			$(CC) $(OBJS_GRAPH) -lSDL -lSDL_image -o $(NAME_GRAPH)

$(NAME_LIB):
			$(CC) -shared -o $(NAME_LIB) -fPIC $(SRCS_SO) -I $(INCLUDES)

clean:
			$(RM) $(OBJS_SERVER)
			$(RM) $(OBJS_GRAPH)

fclean:			clean
			$(RM) $(NAME)
			$(RM) $(NAME_IA)
			$(RM) $(NAME_GRAPH)
			$(RM) $(NAME_LIB)

re:			fclean all
