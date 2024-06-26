#ifndef SO_LONG_H
#define SO_LONG_H
#include "./get_next_line/get_next_line.h"
#include "./mlx/mlx.h"
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ESC_KEY 53
#define UP_KEY_W 13
#define UP_KEY_ARROW 126
#define LEFT_KEY_A 0
#define LEFT_KEY_ARROW 123
#define DOWN_KEY_S 1
#define DOWN_KEY_ARROW 125
#define RIGHT_KEY_D 2
#define RIGHT_KEY_ARROW 124

typedef struct s_character {
  int col;
  int row;
  int score;
  int moves_count;
  void *spirites[4];
  void *curr_animation;
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

// DFS or FLOOD FILL implmentations
void flood_fill(t_game_map *map, int col, int row, int **visited);
int has_valid_path(t_game_state *state);
void set_2d_position(int position[2], int x, int y);
int **create_visited_positions_tracker(t_game_state *state);
void deallocate_visited_positions_tracker(t_game_state *state, int **tracker);

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

#endif
