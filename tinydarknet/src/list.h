#ifndef LIST_H
#define LIST_H
#include "darknet.h"

matrix make_matrix(int rows, int cols);
list *make_list();
int list_find(list *l, void *val);

void list_insert(list *, void *);


void free_list_contents(list *l);

#endif
