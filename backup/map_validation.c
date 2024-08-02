/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:48:59 by msennane          #+#    #+#             */
/*   Updated: 2024/08/02 13:06:12 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdbool.h>
#include <string.h>

int	check_duplicate_elements(t_game_state *state)
{
	int	exit_count;
	int	player_count;

	exit_count = count_map_characters(&state->map, 'E');
	player_count = count_map_characters(&state->map, 'P');
	if (exit_count > 1)
	{
		ft_printf("Error\nMultiple exits detected\n");
		return (1);
	}
	if (player_count > 1)
	{
		ft_printf("Error\nMultiple players detected\n");
		return (1);
	}
	return (0);
}

int	check_map_rectangular(const t_game_map *map)
{
	int	row;

	row = 0;
	while (row < map->rows)
	{
		// strlen
		if ((int)strlen(map->layout[row]) != map->cols)
		{
			ft_printf("Error\n The map is not rectangular\n");
			return (0);
		}
		row++;
	}
	return (1);
}

int	check_map_surrounded_by_walls(t_game_map *map)
{
	int	row;

	row = 1;
	if (!is_row_all_walls(map->layout[0])
		|| !is_row_all_walls(map->layout[map->rows - 1]))
	{
		ft_printf("Error\n The map is not surrounded by walls\n");
		return (0);
	}
	while (row < map->rows - 1)
	{
		if (map->layout[row][0] != '1' || map->layout[row][map->cols
			- 1] != '1')
		{
			ft_printf("Error\n The map is not surrounded by walls\n");
			return (0);
		}
		row++;
	}
	return (1);
}

static void	find_exit_and_count_collectibles(t_game_state *state, int *exit_row,
		int *exit_col, int *collectibles_count)
{
	int	row;
	int	col;

	row = 0;
	while (row < state->map.rows)
	{
		col = 0;
		while (col < state->map.cols)
		{
			if (state->map.layout[row][col] == 'E')
			{
				*exit_row = row;
				*exit_col = col;
			}
			else if (state->map.layout[row][col] == 'C')
				(*collectibles_count)++;
			col++;
		}
		row++;
	}
}

int	check_path_to_collectibles(t_game_state *state)
{
	int		exit_row;
	int		exit_col;
	int		collectibles_count;
	char	original_exit;

	exit_row = -1;
	exit_col = -1;
	collectibles_count = 0;
	find_exit_and_count_collectibles(state, &exit_row, &exit_col,
		&collectibles_count);
	original_exit = state->map.layout[exit_row][exit_col];
	state->map.layout[exit_row][exit_col] = '1';
	state->map.flood_fill_exit = false;
	if (!has_valid_path(state))
	{
		state->map.layout[exit_row][exit_col] = original_exit;
		return (0);
	}
	state->map.layout[exit_row][exit_col] = original_exit;
	state->map.flood_fill_exit = true;
	if (!has_valid_path(state))
		return (0);
	return (1);
}
