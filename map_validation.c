/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:48:59 by msennane          #+#    #+#             */
/*   Updated: 2024/07/30 16:46:04 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <string.h>

int check_duplicate_elements(t_game_state *state) {
  int exit_count;
  int player_count;

  exit_count = count_map_characters(&state->map, 'E');
  player_count = count_map_characters(&state->map, 'P');

  if (exit_count > 1) {
    // to be replaced by my own printf
    printf("Error\nMultiple exits detected\n");
    return (1);
  }
  if (player_count > 1) {
    // to be replaced by my own printf
    printf("Error\nMultiple players detected\n");
    return (1);
  }
  return (0);
}

int check_map_rectangular(const t_game_map *map) {
  int row;

  row = 0;
  while (row < map->rows) {
    // to be replaced by my own strlen function
    if ((int)strlen(map->layout[row]) != map->cols) {
      // to be replaced by my own printf
      printf("Error\n The map is not rectangular\n");
      return (0);
    }
    row++;
  }
  return (1);
}

int check_map_surrounded_by_walls(t_game_map *map) {
  int row;
  row = 1;

  if (!is_row_all_walls(map->layout[0]) ||
      !is_row_all_walls(map->layout[map->rows - 1])) {
    // to be replaced by my own printf
    printf("Error\n The map is not surrounded by walls\n");
    return (0);
  }

  while (row < map->rows - 1) {
    if (map->layout[row][0] != '1' || map->layout[row][map->cols - 1] != '1') {
      // to be replaced by my own printf
      printf("Error\n The map is not surrounded by walls\n");
      return (0);
    }
    row++;
  }
  return (1);
}

int check_path_to_collectibles(t_game_state *state) {
  int row;
  int col;

  row = 0;
  while (row < state->map.rows) {
    col = 0;
    while (col < state->map.cols) {
      if (state->map.layout[row][col] == 'C') {
        state->level_exit.col = col;
        state->level_exit.row = row;
        if (!has_valid_path(state)) {
          // to be replaced by my own printf
          printf("Error\n No path to collectibles\n");
          return (0);
        }
      }
      col++;
    }
    row++;
  }
  return (1);
}
