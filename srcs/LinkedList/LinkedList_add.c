/*
** LinkedList.c for PSU_2015_zappy in /home/pasteu_e/rendu/PSU_2015_zappy
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sat Jun 11 17:47:03 2016 Etienne Pasteur
** Last update Sun Jun 26 16:15:51 2016 Etienne Pasteur
*/

#include "LinkedList.h"

static bool	addElemFront(LinkedList *this, void *data);
static bool	addElemEnd(LinkedList *this, void *data);
static bool	addElemAtPos(LinkedList *this, int pos, void *data);

void		initListPtrFuncAdd(LinkedList *this)
{
  this->addElemFront = &addElemFront;
  this->addElemEnd = &addElemEnd;
  this->addElemAtPos = &addElemAtPos;
}

static bool	addElemFront(LinkedList *this, void *data)
{
  t_list	*newElem;

  newElem = xmalloc(sizeof(t_list));
  newElem->data = data;
  newElem->prev = this->myList->prev;
  newElem->next = this->myList;
  this->myList->prev->next = newElem;
  this->myList->prev = newElem;
  return (true);
}

static bool	addElemEnd(LinkedList *this, void *data)
{
  t_list	*newElem;

  newElem = xmalloc(sizeof(t_list));
  newElem->data = data;
  newElem->prev = this->myList;
  newElem->next = this->myList->next;
  this->myList->next->prev = newElem;
  this->myList->next = newElem;
  return (true);
}

static bool	addElemAtPos(LinkedList *this, int pos, void *data)
{
  t_list	*it;
  int		i;
  t_list	*newElem;

  i = -1;
  it = this->myList->next;
  while (it != this->myList) {
    if (++i == pos) {
      newElem = xmalloc(sizeof(t_list));
      newElem->data = data;
      newElem->prev = it;
      newElem->next = it->next;
      it->next->prev = newElem;
      it->next = newElem;
      return (true);
    }
    it = it->next;
  }
  return (false);
}
