/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:50:05 by msennane          #+#    #+#             */
/*   Updated: 2024/07/29 18:53:43 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "so_long.h"
#include <stdio.h>

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

int count_collectibles(t_game_map *map) {
  int count;
  int i;
  int j;
  count = 0;
  i = 0;
  while (i < map->rows) {
    j = 0;
    while (j < map->cols) {
      if (map->layout[i][j] == 'C')
        count++;
      j++;
    }
    i++;
  }
  return (count);
}

int load_and_parse_map(t_game_state *state) {
  int fd;
  char *line;
  initialize_queue_map(&state->parse_queue);
  fd = open(state->map.file_path, O_RDONLY);
  if (-1 == fd) {
    // replace printf with own implmentation later!!!
    printf("Map file could not be opened!!!");
    close(fd);
    return (0);
  }
  line = get_next_line(fd);
  while (line != NULL) {
    add_to_queue(&state->parse_queue, ft_strtrim(line, "\n")); // Trim new line here
    // enqueue_line(&params->q, ft_strtrim(line, "\n"));
    free(line);
    line = get_next_line(fd);
  }
  load_map_from_queue(&state->parse_queue, &state->map);
  locate_player_and_exit_positions(state);
  state->map.total_collectibles = count_collectibles(&state->map);
  close(fd);
  return (1);
}

void free_map_layout(t_game_map *map) {
  int i;
  if (!map->layout)
    return;
  i = 0;

  while (i < map->rows) {
    free(map->layout[i]);
    i++;
  }
  free(map->layout);
  map->layout = NULL;
}
