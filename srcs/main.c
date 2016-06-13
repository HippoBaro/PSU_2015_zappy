//
// Created by pasteu_e on 06/06/16.
//

#include <Drone.h>
#include <assert.h>
#include "LinkedList.h"

// JUST A MAIN TEST FOR THE LINKEDLIST MODULE

typedef struct s_data {
    int id;
} t_data;

void testFree(void *elem) {
    printf("Free Value: %d\n", ((t_data *) elem)->id);
}

bool predic(void *elem, void *userData) {
    if (((t_data *) elem)->id == (int) userData)
        return (true);
    return (false);
}

void actOnElem(void *elem, void *userData) {
    printf("ELEM Value: %d\n", ((t_data *) elem)->id);
}

static void TestLinkedList() {
    LinkedList *list;
    t_data *data1;
    t_data *data2;
    t_data *data3;
    t_data *data4;
    t_data *data5;

    t_list *elem;

    data1 = xmalloc(sizeof(t_data *));
    data1->id = 1;
    data2 = xmalloc(sizeof(t_data *));
    data2->id = 2;
    data3 = xmalloc(sizeof(t_data *));
    data3->id = 3;
    data4 = xmalloc(sizeof(t_data *));
    data4->id = 4;
    data5 = xmalloc(sizeof(t_data *));
    data5->id = 5;


    list = CreateLinkedList();
    list->addElemFront(list, (void *) data1);
    list->addElemFront(list, (void *) data2);
    list->addElemFront(list, (void *) data3);
    list->addElemFront(list, (void *) data4);
    list->addElemFront(list, (void *) data5);
    list->addElemAtPos(list, 0, data3);

    elem = list->getElementAtPos(list, 0);
    if (elem != NULL)
        printf("First Value: %d\n", ((t_data *) elem->data)->id);

    /* if (list->removeElemAtPos(list, 0) == true) */
    /*   printf("Yep!\n"); */
    /* if (list->removeElemAtPos(list, 0) == true) */
    /*   printf("Yep!\n"); */
    /* if (list->removeElemAtPos(list, 0) == true) */
    /*   printf("Yep!\n"); */
    /* if (list->removeElemAtPos(list, 0) == true) */
    /*   printf("Yep!\n"); */
    /* if (list->removeElemAtPos(list, 0) == true) */
    /*   printf("Yep!\n"); */

    elem = list->firstElementFromPredicate(list, &predic, (void *) 5);
    if (elem != NULL)
        printf("Predic Value: %d\n", ((t_data *) elem->data)->id);
    list->freeThisElem(list, &testFree, elem);

    list->forEachElements(list, &actOnElem, "toto");
    list->forEachElements(list, (void (*)(void *, void *)) lambda(void *, (void *param, void *userData), {
        printf("ELEM Value with LAMBDA: %d %s\n", ((t_data *) param)->id, (string) userData);
    }), "toto2");

    if (list->freeAll(list, &testFree) == true)
        printf("Yep!\n");

    list->Free(list);
    free(data1);
    free(data2);
    free(data3);
    free(data4);
    free(data5);
}

static void TestDrone() {
    Drone   *drone = CreateDrone();
    string  inventory;

    printf("List inventory : %s\n", inventory = drone->ListInventory(drone));
    free(inventory);

    puts("Adding one item...");
    drone->inventory->addElemEnd(drone->inventory, CreateItemFrom(THYSTAME));
    printf("List inventory : %s\n", inventory = drone->ListInventory(drone));
    free(inventory);

    puts("Adding several ones...");
    drone->inventory->addElemEnd(drone->inventory, CreateItemFrom(LINEMATE));
    drone->inventory->addElemEnd(drone->inventory, CreateItemFrom(SIBUR));

    printf("List inventory : %s\n", inventory = drone->ListInventory(drone));
    free(inventory);

    printf("Count = %d\n", drone->inventory->countLinkedList(drone->inventory));
    puts("Deleting SIBUR....");
    t_list *elem = drone->inventory->firstElementFromPredicate(drone->inventory, lambda(bool, (void *item, void *test), {
      if (((Item *)item)->type == SIBUR)
          return true;
      return false;
    }), NULL);
    assert(elem != NULL);
    drone->inventory->freeThisElem(drone->inventory, ((Item *)elem->data)->Free, elem);
    printf("Count = %d\n", drone->inventory->countLinkedList(drone->inventory));
    printf("List inventory : %s\n", inventory = drone->ListInventory(drone));
    free(inventory);

    puts("Freeing everything...");
    drone->Free(drone);
}

int main(void) {
    //puts("Testing LINKEDLIST :");
    //TestLinkedList();
    TestDrone();
    return 0;
}
