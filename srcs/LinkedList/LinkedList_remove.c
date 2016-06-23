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

static bool removeThisElem(LinkedList *this, t_list *elem);

static bool removeElemFront(LinkedList *this);

static bool removeElemEnd(LinkedList *this);

static bool removeElemAtPos(LinkedList *this, int pos);

void initListPtrFuncRemove(LinkedList *this) {
    this->removeThisElem = &removeThisElem;
    this->removeElemFront = &removeElemFront;
    this->removeElemEnd = &removeElemEnd;
    this->removeElemAtPos = &removeElemAtPos;
}

static bool removeThisElem(LinkedList *this, t_list *elem) {
    t_list *it;

    it = this->myList->next;
    while (it != this->myList) {
        if (it == elem) {
            it->prev->next = it->next;
            it->next->prev = it->prev;
            xfree(it, sizeof(t_list));
            return (true);
        }
        it = it->next;
    }
    return (false);
}

static bool removeElemFront(LinkedList *this) {
    t_list *it;

    it = this->myList->next;
    if (it != this->myList) {
        it->prev->next = it->next;
        it->next->prev = it->prev;
        xfree(it, sizeof(t_list));
        return (true);
    }
    return (false);
}

static bool removeElemEnd(LinkedList *this) {
    t_list *it;

    it = this->myList->prev;
    if (it != this->myList) {
        it->prev->next = it->next;
        it->next->prev = it->prev;
        xfree(it, sizeof(t_list));
        return (true);
    }
    return (false);
}

static bool removeElemAtPos(LinkedList *this, int pos) {
    t_list *it;
    int i;

    i = 0;
    it = this->myList->next;
    while (it != this->myList) {
        if (i == pos) {
            it->prev->next = it->next;
            it->next->prev = it->prev;
            xfree(it, sizeof(t_list));
            return (true);
        }
        it = it->next;
        i += 1;
    }
    return (false);
}