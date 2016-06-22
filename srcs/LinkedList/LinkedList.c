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

static void Free(LinkedList *this);

void initListPtrFunc(LinkedList *this) {
    this->Free = &Free;
    initListPtrFuncAdd(this);
    initListPtrFuncForEach(this);
    initListPtrFuncFree(this);
    initListPtrFuncGetElem(this);
    initListPtrFuncRemove(this);
    initListPtrFuncUtils(this);
}

LinkedList *CreateLinkedList() {
    LinkedList *this;

    this = xmalloc(sizeof(LinkedList));
    initListPtrFunc(this);
    this->myList = xmalloc(sizeof(t_list));
    this->myList->prev = this->myList;
    this->myList->next = this->myList;
    return (this);
}

static void Free(LinkedList *this) {
    if (this->countLinkedList(this) > 0)
        Log(WARNING, "You're freeing a non-empty linkedList !");
    xfree(this->myList, sizeof(t_list));
    this->myList = NULL;
    xfree(this, sizeof(LinkedList));
}