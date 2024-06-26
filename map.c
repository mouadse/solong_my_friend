#include "so_long.h"

void initialize_map(t_game_map *map) {
  map->cols = 0;
  map->rows = 0;
  map->file_path = NULL;
  map->layout = NULL;
}

void load_map_from_queue(t_map_parse_queue *queue, t_game_map *map) {
  int i;
  int max_cols;

  map->rows = get_queue_size(queue);
  map->layout = malloc(sizeof(char *) * map->rows);
  if (!map->layout) {
    // to be replaced later by my owm printf
    printf("Malloc failed big time!!!\n");
    exit(EXIT_FAILURE);
  }
  i = 0;
  max_cols = 0;

  while (i < map->rows) {
    // strlen to replaced by my own strlen function later
    map->layout[i] = remove_from_queue(queue);
    if ((int)strlen(map->layout[i]) > max_cols)
      max_cols = strlen(map->layout[i]);
    i++;
  }
  map->cols = max_cols;
}
