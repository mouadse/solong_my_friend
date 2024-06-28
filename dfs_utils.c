#include "so_long.h"

void set_2d_position(int position[2], int x, int y) {
  position[0] = x;
  position[1] = y;
}

int **create_visited_positions_tracker(t_game_state *state) {
  int i;
  int **tracker;

  tracker = malloc(sizeof(int *) * state->map.cols * state->map.rows);
  if (!tracker)
    return (NULL);
  i = 0;
  while (i < state->map.cols * state->map.rows) {
    tracker[i] = malloc(sizeof(int) * 2);
    if (!tracker)
      return (NULL);
    i++;
  }
  return (tracker);
}
