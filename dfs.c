#include "so_long.h"
#include <stdio.h>

void flood_fill(t_game_map *map, int col, int row, int **visited) {
  // Base case: Check if current cell is out of bounds or already visited or
  // blocked
  if (col < 0 || col >= map->cols || row < 0 || row >= map->rows)
    return;
  if (visited[row][col] == 1 || map->layout[row][col] == '1')
    return;

  // Mark the current cell as visited
  visited[row][col] = 1;
  // Recursively apply flood fill to neighboring cells
  flood_fill(map, col + 1, row, visited); // Right
  flood_fill(map, col - 1, row, visited); // Left
  flood_fill(map, col, row + 1, visited); // Down
  flood_fill(map, col, row - 1, visited); // Up
}

int has_valid_path(t_game_state *state) {
  int **visited;
  int i, j;

  // Allocate memory for visited array
  visited = malloc(sizeof(int *) * state->map.rows);
  for (i = 0; i < state->map.rows; i++) {
    visited[i] = malloc(sizeof(int) * state->map.cols);
    for (j = 0; j < state->map.cols; j++) {
      visited[i][j] = 0;
    }
  }

  // Start flood fill from the player's starting position
  flood_fill(&state->map, state->player.col, state->player.row, visited);

  // Check if the target position has been visited
  if (visited[state->map.exit_position.row][state->map.exit_position.col] ==
      1) {
    deallocate_visited_positions_tracker(state, visited);
    return 1;
  }

  deallocate_visited_positions_tracker(state, visited);
  printf("Error\n❌ No valid path found ❌ \n");
  return 0;
}
