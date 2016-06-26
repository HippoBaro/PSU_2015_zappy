/*
** graph.c for zap in /home/pasteu_e/rendu/PSU_2015_zappy/GraphClient
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 23:08:10 2016 Etienne Pasteur
** Last update Sun Jun 26 23:09:32 2016 Etienne Pasteur
*/

#include "GraphClient.h"

bool		attempt_action(t_ecran *val)
{
  SDL_Event	event;

  while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
	return (false);
      else if (event.type == SDL_KEYDOWN)
	{
	  if (event.key.keysym.sym == SDLK_ESCAPE)
	    return (false);
	  if (event.key.keysym.sym == SDLK_LEFT)
	    val->x > 0 ? val->x -= 1 : 0;
	  if (event.key.keysym.sym == SDLK_UP)
	    val->y > 0 ? val->y -= 1 : 0;
	  if (event.key.keysym.sym == SDLK_RIGHT)
	    val->x + 10 < val->terrain_x ? val->x += 1 : 0;
	  if (event.key.keysym.sym == SDLK_DOWN)
	    val->y + 10 < val->terrain_y ? val->y += 1 : 0;
	  draw_terrain(val);

	}
    }
  return (true);
}

bool		displayGraph(t_valGraph *v)
{
  if (v->val.ecran == NULL)
    {
      v->val.ecran = SDL_SetVideoMode(
				      v->val.terrain_x < 10 ? v->val.terrain_x * 100 : 1000,
				      v->val.terrain_y < 10 ? v->val.terrain_y * 100 : 1000, 32,
				      SDL_HWSURFACE);
      draw_terrain(&v->val);
    }
  else if (attempt_action(&v->val) == false)
    return (false);
  return (true);
}

void		initVarGraph(t_valGraph *v)
{
  v->val.x = 0;
  v->val.y = 0;
  v->val.ecran = NULL;
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Zappy", NULL);
  v->val.dirt = IMG_Load("./GraphClient/assets/dirt.jpg");
  v->val.grass = IMG_Load("./GraphClient/assets/grass.jpg");
  v->val.nourriture = IMG_Load("./GraphClient/assets/food.png");
  v->val.linemate = IMG_Load("./GraphClient/assets/rock1.png");
  v->val.deraumere = IMG_Load("./GraphClient/assets/rock2.png");
  v->val.sibur = IMG_Load("./GraphClient/assets/rock3.png");
  v->val.mendiane = IMG_Load("./GraphClient/assets/rock4.png");
  v->val.phiras = IMG_Load("./GraphClient/assets/rock5.png");
  v->val.thystame = IMG_Load("./GraphClient/assets/rock6.png");
  srand((unsigned int) time(NULL));
  v->req = v->net->Receive(v->net, NULL);
}

void		freeVariableGraph(t_valGraph *v)
{
  v->net->DeleteNetwork(v->net);
  free_terrain(&v->val);
  SDL_FreeSurface(v->val.dirt);
  SDL_FreeSurface(v->val.grass);
  SDL_FreeSurface(v->val.nourriture);
  SDL_FreeSurface(v->val.linemate);
  SDL_FreeSurface(v->val.deraumere);
  SDL_FreeSurface(v->val.sibur);
  SDL_FreeSurface(v->val.mendiane);
  SDL_FreeSurface(v->val.phiras);
  SDL_FreeSurface(v->val.thystame);
  SDL_Quit();
}
