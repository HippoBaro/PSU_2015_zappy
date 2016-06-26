/*
** LinkedList.c for PSU_2015_zappy in /home/pasteu_e/rendu/PSU_2015_zappy
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sat Jun 11 17:47:03 2016 Etienne Pasteur
** Last update Sun Jun 26 16:21:18 2016 Etienne Pasteur
*/

#include "LinkedList.h"

static bool	freeThisElem(LinkedList *this, void (*freeFunc)(void *data),
			     t_list *elem);
static bool	freeElemFront(LinkedList *this, void (*freeFunc)(void *elem));
static bool	freeElemEnd(LinkedList *this, void (*freeFunc)(void *elem));
static bool	freeElemAtPos(LinkedList *this, int pos,
			      void (*freeFunc)(void *elem));

void		initListPtrFuncFree(LinkedList *this)
{
  this->freeThisElem = &freeThisElem;
  this->freeElemFront = &freeElemFront;
  this->freeElemEnd = &freeElemEnd;
  this->freeElemAtPos = &freeElemAtPos;
}

static bool	freeThisElem(LinkedList *this, void (*freeFunc)(void *data),
			     t_list *elem)
{
  t_list	*it;

  it = this->myList->next;
  while (it != this->myList)
    {
      if (it == elem)
	{
	  it->prev->next = it->next;
	  it->next->prev = it->prev;
	  if (freeFunc != NULL)
	    freeFunc(it->data);
	  xfree(it, sizeof(t_list));
	  return (true);
	}
      it = it->next;
    }
  return (false);
}

static bool	freeElemFront(LinkedList *this, void (*freeFunc)(void *elem))
{
  t_list	*it;

  it = this->myList->next;
  if (it != this->myList)
    {
      it->prev->next = it->next;
      it->next->prev = it->prev;
      if (freeFunc != NULL)
	freeFunc(it->data);
      xfree(it, sizeof(t_list));
      return (true);
    }
  return (false);
}

static bool	freeElemEnd(LinkedList *this, void (*freeFunc)(void *elem))
{
  t_list	*it;

  it = this->myList->prev;
  if (it != this->myList)
    {
      it->prev->next = it->next;
      it->next->prev = it->prev;
      if (freeFunc != NULL)
	freeFunc(it->data);
      xfree(it, sizeof(t_list));
      return (true);
    }
  return (false);
}

static bool	freeElemAtPos(LinkedList *this, int pos,
			      void (*freeFunc)(void *elem))
{
  t_list	*it;
  int		i;

  i = 0;
  it = this->myList->next;
  while (it != this->myList)
    {
      if (i == pos)
	{
	  it->prev->next = it->next;
	  it->next->prev = it->prev;
	  if (freeFunc != NULL)
	    freeFunc(it->data);
	  xfree(it, sizeof(t_list));
	  return (true);
	}
      it = it->next;
      i += 1;
    }
  return (false);
}
