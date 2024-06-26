#ifndef SO_LONG_H
#define SO_LONG_H
#include "./mlx/mlx.h"

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
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

#endif
