/*
** LinkedList.c for PSU_2015_zappy in /home/pasteu_e/rendu/PSU_2015_zappy
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sat Jun 11 17:47:03 2016 Etienne Pasteur
** Last update Sun Jun 12 15:45:57 2016 Etienne Pasteur
*/

#include "LinkedList.h"

static t_list *getElementFirst(LinkedList *this);

static t_list *getElementEnd(LinkedList *this);

static t_list *getElementAtPos(LinkedList *this, int pos);

static t_list *firstElementFromPredicate(LinkedList *this,
                                         bool (*predicate)(void *elem,
                                                           void *userData),
                                         void *someData);

void initListPtrFuncGetElem(LinkedList *this) {
    this->getElementFirst = &getElementFirst;
    this->getElementEnd = &getElementEnd;
    this->getElementAtPos = &getElementAtPos;
    this->firstElementFromPredicate = &firstElementFromPredicate;
}

static t_list *getElementFirst(LinkedList *this) {
    if (this->myList->next != this->myList)
        return (this->myList->next);
    return (NULL);
}

static t_list *getElementEnd(LinkedList *this) {
    if (this->myList->prev != this->myList)
        return (this->myList->prev);
    return (NULL);
}

static t_list *getElementAtPos(LinkedList *this, int pos) {
    t_list *it;
    int i;

    i = 0;
    it = this->myList->next;
    while (it != this->myList) {
        if (i == pos) {
            return (it);
        }
        it = it->next;
        i += 1;
    }
    return (NULL);
}

static t_list *firstElementFromPredicate(LinkedList *this,
                                         bool (*predicate)(void *elem,
                                                           void *userData),
                                         void *someData) {
    t_list *it;

    it = this->myList->next;
    while (it != this->myList) {
        if (predicate(it->data, someData) == true)
            return (it);
        it = it->next;
    }
    return (NULL);
}