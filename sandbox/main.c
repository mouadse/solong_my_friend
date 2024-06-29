#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct t_node {
  int data;
  struct t_node *next;
} node;

typedef node *lemon;

node *create_node(int val) {
  lemon l1 = malloc(sizeof(node));
  if (!l1)
    return (NULL);
  l1->data = val;
  l1->next = NULL;
  return (l1);
}

typedef struct s_list {
  lemon front;
  lemon back;
} list;

void append_to_list(node *node, list *list) {
  assert(list != NULL);
  if (list->front == NULL)
    list->front = list->back = node;
  else {
    list->back->next = node;
    list->back = node;
  }
}

void init_list(list *lst) {
  lst->front = NULL;
  lst->back = NULL;
}

void display_list(list *lst) {
  assert(lst != NULL);
  lemon node = lst->front;
  while (node) {
    printf("The value is %d\n", node->data);
    node = node->next;
  }
}

void free_list(list *lst) {
  assert(lst != NULL);
  lemon node = lst->front;
  while (node) {
    lemon curr = node;
    node = node->next;
    free(curr);
  }
  free(lst);
}

void remove_node(list *lst, int val) {
  assert(lst != NULL);
  lemon curr, prev, next;
  curr = next = lst->front;
  if (curr->data == val) {
    lemon tmp = curr;
    lst->front = curr->next;
    free(tmp);
  } else {
    while (curr != NULL && curr->data != val) {
      next = next->next;
      prev = curr;
      curr = next;
    }
    prev->next = curr->next;
    free(curr);
  }
}

int main(void) {
  list *lst = malloc(sizeof(list));
  init_list(lst);
  for (int i = 0; i < 10; i++) {
    lemon node = create_node(i);
    append_to_list(node, lst);
  }
  // remove_node(lst, 4);
  display_list(lst);
  free_list(lst);
  return (EXIT_SUCCESS);
}
