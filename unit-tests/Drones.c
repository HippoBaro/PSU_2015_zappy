//
// Created by barrauh on 6/13/16.
//

#include <Drone.h>
#include <assert.h>
#include "Map.h"

void TestDrone() {
    Map     *world = CreateMap(5, 5);
    Drone   *drone = CreateDrone(world, 0, 0);
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
    drone->inventory->freeThisElem(drone->inventory, (void (*)(void *)) DestroyItem, elem);
    printf("Count = %d\n", drone->inventory->countLinkedList(drone->inventory));
    printf("List inventory : %s\n", inventory = drone->ListInventory(drone));
    free(inventory);

    puts("Freeing everything...");
    drone->Free(drone);
}

#if UNIT_TEST
void		TestEntryPoint()
{
  test_all_map();
}
#endif
