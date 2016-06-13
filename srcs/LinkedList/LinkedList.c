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
#include "Item.h"

static int countLinkedList(LinkedList *this);

static bool addElemFront(LinkedList *this, void *data);

static bool addElemEnd(LinkedList *this, void *data);

static bool addElemAtPos(LinkedList *this, int pos, void *data);

static bool removeThisElem(LinkedList *this, t_list *elem);

static bool removeElemFront(LinkedList *this);

static bool removeElemEnd(LinkedList *this);

static bool removeElemAtPos(LinkedList *this, int pos);

static bool freeThisElem(LinkedList *this, void (*freeFunc)(void *elem), t_list *elem);

static bool freeElemFront(LinkedList *this, void (*freeFunc)(void *elem));

static bool freeElemEnd(LinkedList *this, void (*freeFunc)(void *elem));

static bool freeElemAtPos(LinkedList *this, int pos, void (*freeFunc)(void *elem));

static bool freeAll(LinkedList *this, void (*freeFunc)(void *elem));

static t_list *getElementFirst(LinkedList *this);

static t_list *getElementEnd(LinkedList *this);

static t_list *getElementAtPos(LinkedList *this, int pos);

static t_list *firstElementFromPredicate(LinkedList *this, bool (*predicate)(void *elem, void *userData),
                                         void *someData);

static void forEachElements(LinkedList *this, void (*forEachFunc)(void *element, void *userData), void *someData);

static void LinkedListDestroy(LinkedList *this);

static void initPtrFunc(LinkedList *this) {
    this->countLinkedList = &countLinkedList;
    this->addElemFront = &addElemFront;
    this->addElemEnd = &addElemEnd;
    this->addElemAtPos = &addElemAtPos;
    this->removeThisElem = &removeThisElem;
    this->removeElemFront = &removeElemFront;
    this->removeElemEnd = &removeElemEnd;
    this->removeElemAtPos = &removeElemAtPos;
    this->freeThisElem = &freeThisElem;
    this->freeElemFront = &freeElemFront;
    this->freeElemEnd = &freeElemEnd;
    this->freeElemAtPos = &freeElemAtPos;
    this->freeAll = &freeAll;
    this->getElementFirst = &getElementFirst;
    this->getElementEnd = &getElementEnd;
    this->getElementAtPos = &getElementAtPos;
    this->firstElementFromPredicate = &firstElementFromPredicate;
    this->forEachElements = &forEachElements;
    this->Free = &LinkedListDestroy;
}

LinkedList *CreateLinkedList() {
    LinkedList *this;

    this = xmalloc(sizeof(LinkedList));
    initPtrFunc(this);
    this->myList = xmalloc(sizeof(t_list));
    this->myList->prev = this->myList;
    this->myList->next = this->myList;
    return (this);
}

static void LinkedListDestroy(LinkedList *this) {
    if (countLinkedList(this) > 0)
        Log(WARNING, "You're freeing a non-empty linkedList !");
    free(this->myList);
    this->myList = NULL;
    free(this);
}

static int countLinkedList(LinkedList *this) {
    t_list *it;
    int i;

    i = 0;
    it = this->myList->next;
    while (it != this->myList) {
        it = it->next;
        i += 1;
    }
    return (i);
}

static bool addElemFront(LinkedList *this, void *data) {
    t_list *newElem;

    newElem = xmalloc(sizeof(t_list));
    newElem->data = data;
    newElem->prev = this->myList->prev;
    newElem->next = this->myList;
    this->myList->prev->next = newElem;
    this->myList->prev = newElem;
    return (true);
}

static bool addElemEnd(LinkedList *this, void *data) {
    t_list *newElem;

    newElem = xmalloc(sizeof(t_list));
    newElem->data = data;
    newElem->prev = this->myList;
    newElem->next = this->myList->next;
    this->myList->next->prev = newElem;
    this->myList->next = newElem;
    return (true);
}

static bool addElemAtPos(LinkedList *this, int pos, void *data) {
    t_list *it;
    int i;
    t_list *newElem;

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

static bool removeThisElem(LinkedList *this, t_list *elem) {
    t_list *it;

    it = this->myList->next;
    while (it != this->myList) {
        if (it == elem) {
            it->prev->next = it->next;
            it->next->prev = it->prev;
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
            return (true);
        }
        it = it->next;
        i += 1;
    }
    return (false);
}

static bool freeThisElem(LinkedList *this, void (*freeFunc)(void *elem), t_list *elem) {
    t_list *it;

    it = this->myList->next;
    while (it != this->myList) {
        if (it == elem) {
            it->prev->next = it->next;
            it->next->prev = it->prev;
            if (freeFunc != NULL)
                freeFunc(it->data);
            free(it);
            return (true);
        }
        it = it->next;
    }
    return (false);
}

static bool freeElemFront(LinkedList *this, void (*freeFunc)(void *elem)) {
    t_list *it;

    it = this->myList->next;
    if (it != this->myList) {
        it->prev->next = it->next;
        it->next->prev = it->prev;
        if (freeFunc != NULL)
            freeFunc(it->data);
        free(it);
        return (true);
    }
    return (false);
}

static bool freeElemEnd(LinkedList *this, void (*freeFunc)(void *elem)) {
    t_list *it;

    it = this->myList->prev;
    if (it != this->myList) {
        it->prev->next = it->next;
        it->next->prev = it->prev;
        if (freeFunc != NULL)
            freeFunc(it->data);
        free(it);
        return (true);
    }
    return (false);
}

static bool freeElemAtPos(LinkedList *this, int pos, void (*freeFunc)(void *elem)) {
    t_list *it;
    int i;

    i = 0;
    it = this->myList->next;
    while (it != this->myList) {
        if (i == pos) {
            it->prev->next = it->next;
            it->next->prev = it->prev;
            freeFunc(it->data);
            free(it);
            return (true);
        }
        it = it->next;
        i += 1;
    }
    return (false);
}

static bool freeAll(LinkedList *this, void (*freeFunc)(void *elem)) {
    t_list *it;
    t_list *tmp;

    it = this->myList->next;
    while (it != this->myList) {
        it->prev->next = it->next;
        it->next->prev = it->prev;
        tmp = it->next;
        if (freeFunc != NULL)
            freeFunc(it->data);
        free(it);
        it = tmp;
    }
    return (true);
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

static t_list *firstElementFromPredicate(LinkedList *this, bool (*predicate)(void *elem, void *userData),
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

static void forEachElements(LinkedList *this, void (*forEachFunc)(void *element, void *userData), void *someData) {
    t_list *it;

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
