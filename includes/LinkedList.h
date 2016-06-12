/*
** LinkedList.h for PSU_2015_zappy in /home/pasteu_e/rendu/PSU_2015_zappy
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sat Jun 11 17:47:57 2016 Etienne Pasteur
** Last update Sun Jun 12 02:08:28 2016 Etienne Pasteur
*/

#ifndef LINKED_LIST_H_
# define LINKED_LIST_H_

# include "Generic.h"

#define LinkedList(type)    LinkedList

typedef struct	s_list
{
  void		*data;
  struct s_list	*next;
  struct s_list	*prev;
}		t_list;

typedef struct	LinkedList
{
  t_list	*myList;

  // Return number of elements in the list
  int		(*countLinkedList)(struct LinkedList *this);
  // Add element at the top of the list
  bool		(*addElemFront)(struct LinkedList *this, void *data);
  // Add element at the bottom of the list
  bool		(*addElemEnd)(struct LinkedList *this, void *data);
  // Add element after the index "pos"
  bool		(*addElemAtPos)(struct LinkedList *this, int pos, void *data);
  // Remove element passed as parameter from the list
  bool		(*removeThisElem)(struct LinkedList *this, t_list *elem);
  // Remove element at the top of the list
  bool		(*removeElemFront)(struct LinkedList *this);
  // Remove element at the bottom of the list
  bool		(*removeElemEnd)(struct LinkedList *this);
  // Remove element at the index "pos" of the list
  bool		(*removeElemAtPos)(struct LinkedList *this, int pos);
  // Remove and free the element passed as parameter from the list
  bool		(*freeThisElem)(struct LinkedList *this, void (*freeFunc)(void *elem), t_list *elem);
  // Remove and free the element at the top of the list
  bool		(*freeElemFront)(struct LinkedList *this, void (*freeFunc)(void *elem));
  // Remove and free the element at the bottom of the list
  bool		(*freeElemEnd)(struct LinkedList *this, void (*freeFunc)(void *elem));
  // Remove and free the element at the index "pos" of the list
  bool		(*freeElemAtPos)(struct LinkedList *this, int pos, void (*freeFunc)(void *elem));
  // Remove and free all the node contain by the list
  bool		(*freeAll)(struct LinkedList *this, void (*freeFunc)(void *elem));
  // Return a pointer to the top of the list
  t_list*	(*getElementFirst)(struct LinkedList *this);
  // Return a pointer to the bottom of the list
  t_list*	(*getElementEnd)(struct LinkedList *this);
  // Return a pointer to the element which is at the index "pos" of the list
  t_list*	(*getElementAtPos)(struct LinkedList *this, int pos);
  // Designed to match pattern defined by function Predicate which return true or false
  t_list*	(*firstElementFromPredicate)(struct LinkedList *this, bool (*predicate)(void *elem, void* userData), void *someData);
  // Designed to browse all the element of the list and to call a func ptr with the current node and userData
  void		(*forEachElements)(struct LinkedList *this, void (*forEachFunc)(void *element, void *userData), void * someData);
}		LinkedList;

// Init the LinkedList and return a pointer which is malloc
LinkedList	*CreateLinkedList();
// Destroy the LinkedList and free the internal list but not the data and free the LinkedList ptr itself
void		LinkedListDestroy(LinkedList *this);

#endif /* !LINKED_LIST_H_ */
