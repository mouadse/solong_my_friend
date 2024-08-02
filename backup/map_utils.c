/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:49:58 by msennane          #+#    #+#             */
/*   Updated: 2024/08/01 23:21:47 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

int	is_valid_map_character(char character)
{
	size_t		i;
	const char	valid_chars[] = {'0', '1', 'C', 'E', 'P'};

	i = 0;
	while (i < sizeof(valid_chars))
	{
		if (character == valid_chars[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_row_all_walls(const char *row)
{
	int	i;

	i = 0;
	while (row[i] != '\0')
	{
		if (row[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	count_map_characters(const t_game_map *map, char target_char)
{
	int	count;
	int	row;
	int	col;

	count = 0;
	row = 0;
	while (row < map->rows)
	{
		col = 0;
		while (col < map->cols)
		{
			if (map->layout[row][col] == target_char)
				count++;
			col++;
		}
		row++;
	}
	return (count);
}

int	validate_map_format(const t_game_map *map)
{
	int	row;
	int	col;

	row = 0;
	while (row < map->rows)
	{
		col = 0;
		while (col < map->cols)
		{
			if (!is_valid_map_character(map->layout[row][col]))
			{
				// to be replaced by my own ft_printf
				return (0);
			}
			col++;
		}
		row++;
	}
	return (1);
}

int	validate_map(const t_game_map *map)
{
	int	num_exits;
	int	num_collectibles;
	int	num_starting_positions;

	num_exits = count_map_characters(map, 'E');
	num_collectibles = count_map_characters(map, 'C');
	num_starting_positions = count_map_characters(map, 'P');
	if (num_exits != 1)
		return (ft_printf("Error\n❌ Num of Exits ❌\n"),
			0);
	if (num_collectibles < 1)
		return (ft_printf("Error\n❌ Num of Coins❌\n"),
			0);
	if (num_starting_positions != 1)
		return (ft_printf("Map must contain exactly one starting position ❌\n"),
			0);
	if (!validate_map_format(map))
		return (ft_printf("Error\n❌ Invalid map format ❌\n"), 0);
	if (!is_row_all_walls(map->layout[0])
		|| !is_row_all_walls(map->layout[map->rows - 1]))
		return (ft_printf("Error\n❌ The map must be enclosed by walls ❌\n"), 0);
	if (!check_map_rectangular(map))
		return (ft_printf("Error\n❌ The map must be rectangular ❌\n"), 0);
	return (1);
}
