/*
** LinkedList.c for PSU_2015_zappy in /home/pasteu_e/rendu/PSU_2015_zappy
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sat Jun 11 17:47:03 2016 Etienne Pasteur
** Last update Sun Jun 26 16:25:26 2016 Etienne Pasteur
*/

#include "LinkedList.h"

static bool	freeThisElemWithData(LinkedList *this,
				     void (*freeFunc)(void *data),
				     t_list *elem);
static void	Free(LinkedList *this);

void		initListPtrFunc(LinkedList *this)
{
  this->freeThisElemWithData = &freeThisElemWithData;
  this->Free = &Free;
  initListPtrFuncAdd(this);
  initListPtrFuncForEach(this);
  initListPtrFuncFree(this);
  initListPtrFuncGetElem(this);
  initListPtrFuncRemove(this);
  initListPtrFuncUtils(this);
}

LinkedList	*CreateLinkedList()
{
  LinkedList	*this;

  this = xmalloc(sizeof(LinkedList));
  initListPtrFunc(this);
  this->myList = xmalloc(sizeof(t_list));
  this->myList->prev = this->myList;
  this->myList->next = this->myList;
  return (this);
}

static bool	freeThisElemWithData(LinkedList *this,
				     void (*freeFunc)(void *data),
				     t_list *elem)
{
  t_list	*it;

  it = this->myList->next;
  while (it != this->myList)
    {
      if (it->data == elem)
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

static void	Free(LinkedList *this)
{
  if (this->countLinkedList(this) > 0)
    Log(WARNING, "You're freeing a non-empty linkedList !");
  xfree(this->myList, sizeof(t_list));
  this->myList = NULL;
  xfree(this, sizeof(LinkedList));
}
