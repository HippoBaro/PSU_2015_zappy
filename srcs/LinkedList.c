/*
** LinkedList.c for PSU_2015_zappy in /home/pasteu_e/rendu/PSU_2015_zappy
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sat Jun 11 17:47:03 2016 Etienne Pasteur
** Last update Sat Jun 11 23:08:14 2016 Etienne Pasteur
*/

#include <LinkedList.h>

static void	printLinkedList(LinkedList *this);
static int	countLinkedList(LinkedList *this);
static bool	addElemFront(LinkedList *this, void *data);
static bool	addElemEnd(LinkedList *this, void *data);
static bool	addElemAtPos(LinkedList *this, int pos, void *data);
static bool	removeElemFront(LinkedList *this);
static bool	removeElemEnd(LinkedList *this);
static bool	removeElemAtPos(LinkedList *this, int pos);
static bool	freeElemFront(LinkedList *this, void (*freeFunc)(void *elem));
static bool	freeElemEnd(LinkedList *this, void (*freeFunc)(void *elem));
static bool	freeElemAtPos(LinkedList *this, int pos, void (*freeFunc)(void *elem));
static bool	freeAll(LinkedList *this, void (*freeFunc)(void *elem));
static t_list*	getElementFirst(LinkedList *this);
static t_list*	getElementEnd(LinkedList *this);
static t_list*	getElementAtPos(LinkedList *this, int pos);
static t_list*	FirstElementFromPredicate(LinkedList *this, int (*Predicate)(void *elem, void* data));
static void	forEachElements(LinkedList *this, void (*forEachFunc)(void *element, void *userData));

static void	initPtrFunc(LinkedList *this)
{
  this->printLinkedList = &printLinkedList;
  this->countLinkedList = &countLinkedList;
  this->addElemFront = &addElemFront;
  this->addElemEnd = &addElemEnd;
  this->addElemAtPos = &addElemAtPos;
  this->removeElemFront = &removeElemFront;
  this->removeElemEnd = &removeElemEnd;
  this->removeElemAtPos = &removeElemAtPos;
  this->freeElemFront = &freeElemFront;
  this->freeElemEnd = &freeElemEnd;
  this->freeElemAtPos = &freeElemAtPos;
  this->freeAll = &freeAll;
  this->getElementFirst = &getElementFirst;
  this->getElementEnd = &getElementEnd;
  this->getElementAtPos = &getElementAtPos;
  this->FirstElementFromPredicate = &FirstElementFromPredicate;
  this->forEachElements = &forEachElements;
}

void		LinkedListInit(LinkedList *this)
{
  initPtrFunc(this);
  this->myList = malloc(sizeof(*this->myList));
  if (this->myList != NULL )
    {
      this->myList->prev = this->myList;
      this->myList->next = this->myList;
    }
}

void		LinkedListDestroy(LinkedList *this)
{
  t_list	*it;
  t_list	*next;

  it = this->myList->next;
  while (it != this->myList)
    {
      next = it->next;
      free(it);
      it = next;
    }
  free(this->myList);
  this->myList = NULL;
}

static void	printLinkedList(LinkedList *this)
{
  t_list	*it;
  int		i;

  i = 0;
  it = this->myList->next;
  while (it != this->myList)
    {
      it = it->next;
      i += 1;
    }
  printf("Nb_elem : %d\n", i);
}

static int	countLinkedList(LinkedList *this)
{
  t_list	*it;
  int		i;

  i = 0;
  it = this->myList->next;
  while (it != this->myList)
    {
      it = it->next;
      i += 1;
    }
  return (i);
}

static bool	addElemFront(LinkedList *this, void *data)
{
  t_list	*newElem;

  newElem = malloc(sizeof(*newElem));
  if (newElem != NULL)
    {
      newElem->data = data;
      newElem->prev = this->myList->prev;
      newElem->next = this->myList;
      this->myList->prev->next = newElem;
      this->myList->prev = newElem;
      return (true);
    }
  return (false);
}

static bool	addElemEnd(LinkedList *this, void *data)
{
  t_list	*newElem;

  newElem = malloc(sizeof(*newElem));
  if (newElem != NULL)
    {
      newElem->data = data;
      newElem->prev = this->myList;
      newElem->next = this->myList->next;
      this->myList->next->prev = newElem;
      this->myList->next = newElem;
      return (true);
    }
  return (false);
}

static bool	addElemAtPos(LinkedList *this, int pos, void *data)
{
  t_list	*it;
  int		i;
  t_list	*newElem;

  i = 0;
  it = this->myList->next;
  while (it != this->myList)
    {
      if (i == pos)
	{
	  newElem = malloc(sizeof(*newElem));
	  if (newElem != NULL)
	    {
	      newElem->data = data;
	      newElem->prev = it;
	      newElem->next = it->next;
	      it->next->prev = newElem;
	      it->next = newElem;
	      return (true);
	    }
	  else
	    return (false);
	}
      it = it->next;
      i += 1;
    }
  return (false);
}

static bool	removeElemFront(LinkedList *this)
{
  if (this->myList->next != this->myList)
    {
      this->myList->next->prev->next = this->myList->next->next;
      this->myList->next->next->prev = this->myList->next->prev;
      return (true);
    }
  return (false);
}

static bool	removeElemEnd(LinkedList *this)
{
  if (this->myList->prev != this->myList)
    {
      this->myList->prev->prev->next = this->myList->prev->next;
      this->myList->prev->next->prev = this->myList->prev->prev;
      return (true);
    }
  return (false);
}

static bool	removeElemAtPos(LinkedList *this, int pos)
{

}

static bool	freeElemFront(LinkedList *this, void (*freeFunc)(void *elem))
{

}

static bool	freeElemEnd(LinkedList *this, void (*freeFunc)(void *elem))
{

}

static bool	freeElemAtPos(LinkedList *this, int pos, void (*freeFunc)(void *elem))
{

}

static bool	freeAll(LinkedList *this, void (*freeFunc)(void *elem))
{

}

static t_list*	getElementFirst(LinkedList *this)
{
  if (this->myList->next != this->myList)
    return (this->myList->next);
  return (NULL);
}

static t_list*	getElementEnd(LinkedList *this)
{
  if (this->myList->prev != this->myList)
    return (this->myList->prev);
  return (NULL);
}

static t_list*	getElementAtPos(LinkedList *this, int pos)
{
  t_list	*it;
  int		i;

  i = 0;
  it = this->myList->next;
  while (it != this->myList)
    {
      if (i == pos)
	{
	  return (it);
	}
      it = it->next;
      i += 1;
    }
  return (NULL);
}

static t_list*	FirstElementFromPredicate(LinkedList *this, int (*Predicate)(void *elem, void* data))
{

}

static void	forEachElements(LinkedList *this, void (*forEachFunc)(void *element, void *userData))
{

}
