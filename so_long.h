/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:48:55 by msennane          #+#    #+#             */
/*   Updated: 2024/07/30 16:47:39 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H
#include "./get_next_line/get_next_line.h"
#include "./mlx_linux/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ESC_KEY 65307
#define UP_KEY_W 119
#define UP_KEY_ARROW 65362
#define LEFT_KEY_A 97
#define LEFT_KEY_ARROW 65361
#define DOWN_KEY_S 115
#define DOWN_KEY_ARROW 65364
#define RIGHT_KEY_D 100
#define RIGHT_KEY_ARROW 65363

typedef struct s_character {
  int col;
  int row;
  int score;
  int moves_count;
  void *spirites[4];
  void *curr_animation[4];
  int facing_direction;
} t_character;

typedef struct s_lvl_exit {
  int col;
  int row;
} t_lvl_exit;

typedef struct s_game_assets {
  void *wall_asset;
  void *coin_asset;
  void *floor_asset;
  void *closed_door_asset;
  void *open_door_asset;
} t_game_assets;

typedef struct s_game_map {
  int rows;
  int cols;
  char *file_path;
  char **layout;
  int total_collectibles;
  t_lvl_exit exit_position;
} t_game_map;

typedef struct s_map_line_node {
  char *line_content;
  struct s_map_line_node *next_line;
} t_map_line_node;

typedef struct s_map_parse_queue {
  struct s_map_line_node *first_line;
  struct s_map_line_node *last_line;
} t_map_parse_queue;

typedef struct s_game_state {
  void *mlx_instance;
  void *window_instance;
  t_game_map map;
  t_map_parse_queue parse_queue;
  t_character player;
  t_lvl_exit level_exit;
  t_game_assets assets;
  int game_completed;
} t_game_state;

// Game State Management Functions

void initialize_and_load_player_images(t_game_state *state);
void render_player(t_game_state *state);
void locate_player_and_exit_positions(t_game_state *state);

// Map Parse Queue Functions

void initialize_queue_map(t_map_parse_queue *queue);
int is_queue_empty(t_map_parse_queue *q);
void add_to_queue(t_map_parse_queue *queue, char *line);
char *remove_from_queue(t_map_parse_queue *queue);
int get_queue_size(t_map_parse_queue *queue);

// Game State Management Functions

void initialize_and_load_player_images(t_game_state *state);
void render_player(t_game_state *state);
void locate_player_and_exit_positions(t_game_state *state);
void load_game_textures(t_game_state *state);
void verify_textures_loaded(t_game_state *state);

// DFS or FLOOD FILL implmentations
void flood_fill(t_game_map *map, int col, int row, char **visited);
int has_valid_path(t_game_state *state);
void flood_fill(t_game_map *map, int col, int row, char **visited);
char **allocate_visited_array(int rows, int cols);
void initialize_visited_array(char **visited, int rows, int cols);
void free_visited_array(char **visited, int rows);
int has_valid_path(t_game_state *params);

// Map Parsing Functions

void initialize_map(t_game_map *map);
void load_map_from_queue(t_map_parse_queue *queue, t_game_map *map);
int count_collectibles(t_game_map *map);
int load_and_parse_map(t_game_state *state);
void free_map_layout(t_game_map *map);

// Functions below are for parsing the map file and counting the number of
// collectibles and validating the map format
int is_valid_map_character(char character);
int is_row_all_walls(const char *row);
int count_map_characters(const t_game_map *map, char target_char);
int validate_map_format(const t_game_map *map);
int validate_map(const t_game_map *map);

// Other parsing functions to be added here
void cleanup_game_resources(t_game_state *state);
int process_arguments_and_map(int argc, char **argv, t_game_state *state);
int validate_command_line_arguments(int argc, char **argv, t_game_state *state);

// Movements Functions
int valid_move(t_game_state *state, int row, int col);
void move_sprite_up(t_game_state *state);
void move_sprite_down(t_game_state *state);
void move_sprite_left(t_game_state *state);
void move_sprite_right(t_game_state *state);
int handle_keypress(int keycode, t_game_state *state);

// rendering functions
void render_game_map(t_game_state *state);
// libft utils functions
char *ft_strtrim(const char *s, const char *set);
int check_map_rectangular(const t_game_map *map);
int check_path_to_collectibles(t_game_state *state);
#endif
