//
// Created by pasteu_e on 06/06/16.
//

#include "../includes/LinkedList.h"

typedef struct	s_data
{
  int	id;
}		t_data;

void	testFree(void *elem)
{
  printf("Free Value: %d\n", ((t_data*)elem)->id);
}

bool	predic(void *elem, void *userData)
{
  if (((t_data*)elem)->id == (int*)userData)
    return (true);
  return (false);
}

void actOnElem(void *elem, void *userData)
{
  printf("ELEM Value: %d\n", ((t_data*)elem)->id);
}

int main(void)
{
  LinkedList *list;
  t_data *data1;
  t_data *data2;
  t_data *data3;
  t_data *data4;
  t_data *data5;

  t_list *elem;

  data1 = malloc(sizeof(t_data*));
  data1->id = 1;
  data2 = malloc(sizeof(t_data*));
  data2->id = 2;
  data3 = malloc(sizeof(t_data*));
  data3->id = 3;
  data4 = malloc(sizeof(t_data*));
  data4->id = 4;
  data5 = malloc(sizeof(t_data*));
  data5->id = 5;


  list = CreateLinkedList();
  list->addElemFront(list, (void *)data1);
  list->addElemFront(list, (void *)data2);
  list->addElemFront(list, (void *)data3);
  list->addElemFront(list, (void *)data4);
  list->addElemFront(list, (void *)data5);
  list->addElemAtPos(list, 0, data3);

  elem = list->getElementAtPos(list, 0);
  if (elem != NULL)
    printf("First Value: %d\n", ((t_data*)elem->data)->id);
  list->printLinkedList(list);

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
  /* list->printLinkedList(list); */

  elem = list->firstElementFromPredicate(list, &predic, (void*)5);
  if (elem != NULL)
    printf("Predic Value: %d\n", ((t_data*)elem->data)->id);
  list->freeThisElem(list, &testFree, elem);

  list->forEachElements(list, &actOnElem, "toto");
  list->forEachElements(list,  lambda(void *, (void *param), {
      printf("ELEM Value with LAMBDA: %d\n", ((t_data*)elem)->id);
    }), "toto2");

  if (list->freeAll(list, &testFree) == true)
    printf("Yep!\n");

  list->printLinkedList(list);
  LinkedListDestroy(list);
  free(data1);
  free(data2);
  free(data3);
  free(data4);
  free(data5);
  return (0);
}
