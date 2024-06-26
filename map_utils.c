#include "so_long.h"
#include <stdio.h>

int	is_valid_map_character(char character)
{
	int			i;
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

int	count_map_characters(t_game_map *map, char target_char)
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
				// to be replaced by my own printf
				printf("Invalid char detected !!!");
				return (0);
			}
			col++;
		}
		row++;
	}
	return (1);
}
