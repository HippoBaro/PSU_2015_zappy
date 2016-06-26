//
// Created by pasteu_e on 26/06/16.
//

#ifndef PSU_2015_ZAPPY_GRAPHCLIENT_H
#define PSU_2015_ZAPPY_GRAPHCLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include <assert.h>

#include "Network.h"

typedef struct s_tile {
    int texture;
    int nourriture;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
    SDL_Rect position_nourriture;
    SDL_Rect position_linemate;
    SDL_Rect position_deraumere;
    SDL_Rect position_sibur;
    SDL_Rect position_mendiane;
    SDL_Rect position_phiras;
    SDL_Rect position_thystame;
} t_tile;

typedef struct s_ecran {
    t_tile **terrain;
    int terrain_x;
    int terrain_y;
    int x;
    int y;
    SDL_Surface *ecran;
    SDL_Surface *dirt;
    SDL_Surface *grass;
    SDL_Surface *nourriture;
    SDL_Surface *linemate;
    SDL_Surface *deraumere;
    SDL_Surface *sibur;
    SDL_Surface *mendiane;
    SDL_Surface *phiras;
    SDL_Surface *thystame;
    SDL_Surface *display;
} t_ecran;

typedef struct s_flags {
    char *cmd;
    void   (*ptrF)(char *arg, t_ecran *val);
} t_flags;

typedef struct s_valueGraph {
    t_ecran val;
    Network *net;
    Request *req;
    struct timeval tv;
    char *token;
    char *str_copy;
    char *tmp_string;
} t_valGraph;

typedef struct s_valBct {
    int i;
    int x;
    int y;
    char **tokens;
} t_valBct;

typedef struct s_splitVar {
    char **result;
    size_t count;
    char *last_comma;
    char delim[2];
    size_t idx;
    char *token;
} t_splitVar;

void draw_terrain_next(t_ecran *val, int i, int j, void (*funcPtr[7])(SDL_Rect, t_ecran*, int, int));
void draw_terrain(t_ecran *val);
void fill_randPosGraph(t_ecran *val, int i, int j);
void generate_terrain(t_ecran *val);
void free_terrain(t_ecran *val);
bool attempt_action(t_ecran *val);
void splitVarInit(t_splitVar *v, char *a_str, const char a_delim);
char **str_split(char *a_str, const char a_delim);
void msz(char *arg, t_ecran *val);
void sgt(char *arg, t_ecran *val);
void bctIf(t_valBct *v, t_ecran *val);
void bct(char *arg, t_ecran *val);
void parse_command(char *str, t_ecran *val);
void initVarGraph(t_valGraph *v);
void freeVariableGraph(t_valGraph *v);
void initConnectionWithServer(t_valGraph *v);
bool dataFromServer(t_valGraph *v);
bool displayGraph(t_valGraph *v);
void blitNourriture(SDL_Rect position, t_ecran *val, int i, int j);
void blitLinemate(SDL_Rect position, t_ecran *val, int i, int j);
void blitDeraumere(SDL_Rect position, t_ecran *val, int i, int j);
void blitSibur(SDL_Rect position, t_ecran *val, int i, int j);
void blitMendiane(SDL_Rect position, t_ecran *val, int i, int j);
void blitPhiras(SDL_Rect position, t_ecran *val, int i, int j);
void blitThystame(SDL_Rect position, t_ecran *val, int i, int j);

#endif //PSU_2015_ZAPPY_GRAPHCLIENT_H
