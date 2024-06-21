#ifndef SO_LONG_H
# define SO_LONG_H

# include <assert.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_character
{
	int						x_pos;
	int						y_pos;
	int						collected_coins;
	int						moves_count;
	void					*spirites[4];
	void					*curr_animation;
	int						facing_direction;
}							t_character;

typedef struct s_lvl_exit
{
	int						x_pos;
	int						y_pos;
}							t_lvl_exit;

typedef struct s_game_assets
{
	void					*wall_asset;
	void					*coin_asset;
	void					*floor_asset;
	void					*closed_door_asset;
	void					*open_door_asset;
}							t_game_assets;

typedef struct s_game_map
{
	int						height;
	int						width;
	char					*file_path;
	char					**layout;
	int						total_collectibles;
	t_lvl_exit				exit_position;
}							t_game_map;

struct						s_map_line_node
{
	char					*line_content;
	struct s_map_line_node	*next_line;
};

typedef struct s_map_parse_queue
{
	struct s_map_line_node	*first_line;
	struct s_map_line_node	*last_line;
}							t_map_parse_queue;

typedef struct s_game_state
{
	void					*mlx_instance;
	void					*window_instance;
	t_game_map				map;
	t_map_parse_queue		parse_queue;
	t_character				player;
	t_lvl_exit				level_exit;
	t_game_assets			assets;
	int						game_completed;
}							t_game_state;

#endif
