/*
** LinkedList.c for PSU_2015_zappy in /home/pasteu_e/rendu/PSU_2015_zappy
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sat Jun 11 17:47:03 2016 Etienne Pasteur
** Last update Sun Jun 26 16:33:35 2016 Etienne Pasteur
*/

#include "LinkedList.h"

static void	forEachElements(LinkedList *this,
				void (*forEachFunc)(void *element, void *userData),
				void *someData);
static void	forEachElementsReloadIterator(LinkedList *this,
					      bool (*forEachFunc)(void *element,
								  void *userData),
					      void *someData);

void		initListPtrFuncForEach(LinkedList *this)
{
  this->forEachElements = &forEachElements;
  this->forEachElementsReloadIterator = &forEachElementsReloadIterator;
}

static void	forEachElements(LinkedList *this,
				void (*forEachFunc)(void *element, void *userData),
				void *someData)
{
  t_list	*it;

  if (forEachFunc == NULL) {
    Log(WARNING, "Trying to foreach with a NULL-function pointers.");
    return;
  }
  it = this->myList->next;
  while (it != this->myList) {
    forEachFunc(it->data, someData);
    it = it->next;
  }
}

static void	forEachElementsReloadIterator(LinkedList *this,
					      bool (*forEachFunc)(void *element,
								  void *userData),
					      void *someData)
{
  t_list	*it;

  if (forEachFunc == NULL) {
    Log(WARNING, "Trying to foreach with a NULL-function pointers.");
    return;
  }
  it = this->myList->next;
  while (it != this->myList) {
    if (forEachFunc(it->data, someData) == true) {
      it = this->myList;
    }
  }
}
