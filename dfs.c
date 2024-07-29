#include "so_long.h"
#include <stdio.h>
#define VISITED 1
#define NOT_VISITED 0



void flood_fill(t_game_map *map, int col, int row, char **visited) {
    if (map == NULL || col < 0 || col >= map->cols || row < 0 || row >= map->rows) {
        return;
    }
    if (visited[row][col] == VISITED || map->layout[row][col] == '1') {
        return;
    }
    visited[row][col] = VISITED;
    flood_fill(map, col - 1, row, visited);
    flood_fill(map, col + 1, row, visited);
    flood_fill(map, col, row - 1, visited);
    flood_fill(map, col, row + 1, visited);
}

int has_valid_path(t_game_state *params) {
    if (params == NULL) {
        return 0;
    }
    char **visited = allocate_visited_array(params->map.rows, params->map.cols);
    if (visited == NULL) {
        return 0;
    }
    initialize_visited_array(visited, params->map.rows, params->map.cols);
    flood_fill(&params->map, params->player.col, params->player.row, visited);
    int valid = visited[params->map.exit_position.row][params->map.exit_position.col] == VISITED;
    free_visited_array(visited, params->map.rows);
    if (!valid) {
        printf("Error: No path to collectibles\n");
    }
    return valid;
}

char **allocate_visited_array(int rows, int cols) {
    char **visited = malloc(rows * sizeof(char *));
    if (visited == NULL) {
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        visited[i] = malloc(cols * sizeof(char));
        if (visited[i] == NULL) {
            free_visited_array(visited, i);
            return NULL;
        }
    }
    return visited;
}

void initialize_visited_array(char **visited, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            visited[i][j] = NOT_VISITED;
        }
    }
}

void free_visited_array(char **visited, int rows) {
    for (int i = 0; i < rows; i++) {
        free(visited[i]);
    }
    free(visited);
}


// void flood_fill(t_game_map *map, int col, int row, int **visited) {
//   // Base case: Check if current cell is out of bounds or already visited or
//   // blocked
//   if (col < 0 || col >= map->cols || row < 0 || row >= map->rows)
//     return;
//   if (visited[row][col] == 1 || map->layout[row][col] == '1')
//     return;

//   // Mark the current cell as visited
//   visited[row][col] = 1;
//   // Recursively apply flood fill to neighboring cells
//   flood_fill(map, col + 1, row, visited); // Right
//   flood_fill(map, col - 1, row, visited); // Left
//   flood_fill(map, col, row + 1, visited); // Down
//   flood_fill(map, col, row - 1, visited); // Up
// }

// int has_valid_path(t_game_state *state) {
//   int **visited;
//   int i, j;

//   // Allocate memory for visited array
//   // This code can be replaced with our function to generate tracker much
//   safer visited = malloc(sizeof(int *) * state->map.rows); for (i = 0; i <
//   state->map.rows; i++) {
//     visited[i] = malloc(sizeof(int) * state->map.cols);
//     for (j = 0; j < state->map.cols; j++) {
//       visited[i][j] = 0;
//     }
//   }

//   // Start flood fill from the player's starting position
//   flood_fill(&state->map, state->player.col, state->player.row, visited);

//   // Check if the target position has been visited
//   if (visited[state->map.exit_position.row][state->map.exit_position.col] ==
//       1) {
//     deallocate_visited_positions_tracker(state, visited);
//     return 1;
//   }

//   deallocate_visited_positions_tracker(state, visited);
//   printf("Error\n❌ No valid path found ❌ \n");
//   return 0;
// }
