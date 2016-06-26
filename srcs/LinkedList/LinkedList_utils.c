/*
** LinkedList.c for PSU_2015_zappy in /home/pasteu_e/rendu/PSU_2015_zappy
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sat Jun 11 17:47:03 2016 Etienne Pasteur
** Last update Sun Jun 26 16:35:11 2016 Etienne Pasteur
*/

#include "LinkedList.h"

static int	countLinkedList(LinkedList *this);
static bool	freeAll(LinkedList *this, void (*freeFunc)(void *elem));

void		initListPtrFuncUtils(LinkedList *this)
{
  this->countLinkedList = &countLinkedList;
  this->freeAll = &freeAll;
}

static int	countLinkedList(LinkedList *this)
{
  t_list	*it;
  int		i;

  i = 0;
  it = this->myList->next;
  while (it != this->myList) {
    it = it->next;
    i += 1;
  }
  return (i);
}

static bool	freeAll(LinkedList *this, void (*freeFunc)(void *elem))
{
  t_list	*it;
  t_list	*tmp;

  it = this->myList->next;
  while (it != this->myList) {
    it->prev->next = it->next;
    it->next->prev = it->prev;
    tmp = it->next;
    if (freeFunc != NULL && it->data != NULL)
      freeFunc(it->data);
    xfree(it, sizeof(t_list));
    it = tmp;
  }
  return (true);
}
