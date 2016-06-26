/*
** LinkedList.h for PSU_2015_zappy in /home/pasteu_e/rendu/PSU_2015_zappy
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sat Jun 11 17:47:57 2016 Etienne Pasteur
** Last update Mon Jun 27 00:02:56 2016 Etienne Pasteur
*/

#ifndef LINKED_LIST_H_
# define LINKED_LIST_H_

# include "Generic.h"

# define LinkedList(type)	LinkedList

typedef struct		s_list
{
  void			*data;
  struct s_list		*next;
  struct s_list		*prev;
}			t_list;

typedef struct	LinkedList
{
  t_list	*myList;

  void		(*Free)(struct LinkedList *this);
  int		(*countLinkedList)(struct LinkedList *this);
  bool		(*addElemFront)(struct LinkedList *this, void *data);
  bool		(*addElemEnd)(struct LinkedList *this, void *data);
  bool		(*addElemAtPos)(struct LinkedList *this, int pos, void *data);
  bool		(*removeThisElem)(struct LinkedList *this, t_list *elem);
  bool		(*removeElemFront)(struct LinkedList *this);
  bool		(*removeElemEnd)(struct LinkedList *this);
  bool		(*removeElemAtPos)(struct LinkedList *this, int pos);
  bool		(*freeThisElem)(struct LinkedList *this,
				void (*freeFunc)(void *data), t_list *elem);
  bool		(*freeThisElemWithData)(struct LinkedList *this,
					void (*freeFunc)(void *elem),
					t_list *elem);
  bool		(*freeElemFront)(struct LinkedList *this,
				 void (*freeFunc)(void *elem));
  bool		(*freeElemEnd)(struct LinkedList *this,
			       void (*freeFunc)(void *elem));
  bool		(*freeElemAtPos)(struct LinkedList *this, int pos,
				 void (*freeFunc)(void *elem));
  bool		(*freeAll)(struct LinkedList *this,
			   void (*freeFunc)(void *elem));
  t_list	*(*getElementFirst)(struct LinkedList *this);
  t_list	*(*getElementEnd)(struct LinkedList *this);
  t_list	*(*getElementAtPos)(struct LinkedList *this, int pos);
  t_list	*(*firstElementFromPredicate)(struct LinkedList *this,
					      bool (*predicate)(void *elem,
								void *userData),
					      void *someData);
  void		(*forEachElements)(struct LinkedList *this,
				   void (*forEachFunc)(void *element,
						       void *userData),
				   void *someData);
  void		(*forEachElementsReloadIterator)(struct LinkedList *this,
						 bool (*forEachFunc)(void *element,
								     void *userData),
						 void *someData);
}		LinkedList;

LinkedList	*CreateLinkedList();
void		initListPtrFunc(LinkedList *this);
void		initListPtrFuncAdd(LinkedList *this);
void		initListPtrFuncForEach(LinkedList *this);
void		initListPtrFuncFree(LinkedList *this);
void		initListPtrFuncGetElem(LinkedList *this);
void		initListPtrFuncRemove(LinkedList *this);
void		initListPtrFuncUtils(LinkedList *this);

#endif /* !LINKED_LIST_H_ */
