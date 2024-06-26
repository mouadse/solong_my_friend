#include "so_long.h"

void initialize_queue_map(t_map_parse_queue *queue) {
  queue->first_line = NULL;
  queue->last_line = NULL;
}

int is_queue_empty(t_map_parse_queue *q) { return (q->first_line == NULL); }

void add_to_queue(t_map_parse_queue *queue, char *line) {
  t_map_line_node *node;

  node = malloc(sizeof(t_map_line_node));
  if (!node)
    return;
  node->line_content = line;
  node->next_line = NULL;
  if (is_queue_empty(queue)) {
    queue->first_line = node;
    queue->last_line = node;
  } else {
    queue->last_line->next_line = node;
    queue->last_line = node;
  }
}

char *remove_from_queue(t_map_parse_queue *queue) {
  t_map_line_node *temp;
  char *line;
  if (is_queue_empty(queue))
    return (NULL);
  temp = queue->first_line;
  line = temp->line_content;
  queue->first_line = queue->first_line->next_line;
  free(temp);
  if (!queue->first_line)
    queue->last_line = NULL;
  return (line);
}

int get_queue_size(t_map_parse_queue *queue) {
  t_map_line_node *tmp;
  int size;
  tmp = queue->first_line;
  size = 0;
  while (tmp != NULL) {
    size++;
    tmp = tmp->next_line;
  }
  return (size);
}
