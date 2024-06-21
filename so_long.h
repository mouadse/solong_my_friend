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
	int		x_pos;
	int		y_pos;
	int		collected_coins;
	int		moves_count;
	void	*spirites[4];
	void	*curr_animation;
	int		facing_direction;
}			t_character;

typedef struct s_lvl_exit
{
	int		x_pos;
	int		y_pos;
}			t_lvl_exit;

typedef struct s_game_assets
{
	void	*wall_asset;
	void	*coin_asset;
	void	*floor_asset;
	void	*closed_door_asset;
	void	*open_door_asset;
}			t_game_assets;

#endif
