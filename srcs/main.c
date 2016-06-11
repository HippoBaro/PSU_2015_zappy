//
// Created by pasteu_e on 06/06/16.
//

#include "../includes/LinkedList.h"

typedef struct	s_data
{
  int	id;
}		t_data;

int main(void)
{
  LinkedList *list;
  t_data *data;

  data = malloc(sizeof(t_data*));
  data->id = 5;

  list = malloc(sizeof(LinkedList));
  LinkedListInit(list);
  list->addElemFront(list, (void *)data);
  list->printLinkedList(list);
  LinkedListDestroy(list);
  return (0);
}
