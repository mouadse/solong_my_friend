/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:50:05 by msennane          #+#    #+#             */
/*   Updated: 2024/08/05 14:09:58 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "so_long.h"

void	initialize_map(t_game_map *map)
{
	map->cols = 0;
	map->rows = 0;
	map->file_path = NULL;
	map->layout = NULL;
	map->is_exit_open = false;
	map->flood_fill_exit = false;
}

void	load_map_from_queue(t_map_parse_queue *queue, t_game_map *map)
{
	int	i;
	int	max_cols;

	map->rows = get_queue_size(queue);
	map->layout = malloc(sizeof(char *) * map->rows);
	if (!map->layout)
	{
		ft_printf("Malloc failed big time!!!\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	max_cols = 0;
	while (i < map->rows)
	{
		map->layout[i] = remove_from_queue(queue);
		if ((int)ft_strlen(map->layout[i]) > max_cols)
			max_cols = ft_strlen(map->layout[i]);
		i++;
	}
	map->cols = max_cols;
}

int	count_collectibles(t_game_map *map)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (map->layout[i][j] == 'C')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	load_and_parse_map(t_game_state *state)
{
	int		fd;
	char	*line;

	initialize_queue_map(&state->parse_queue);
	fd = open(state->map.file_path, O_RDONLY);
	if (fd == -1)
		return (close(fd), ft_printf("Map file could not be opened!!!\n"), 0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		add_to_queue(&state->parse_queue, ft_strtrim(line, "\n"));
		free(line);
		line = get_next_line(fd);
	}
	load_map_from_queue(&state->parse_queue, &state->map);
	if (state->map.rows == 0 || state->map.cols == 0)
		return (close(fd), ft_printf("Map is empty!!!\n"), 0);
	return (close(fd), 1);
}

void	free_map_layout(t_game_map *map)
{
	int	i;

	if (!map->layout)
		return ;
	i = 0;
	while (i < map->rows)
	{
		free(map->layout[i]);
		i++;
	}
	free(map->layout);
	map->layout = NULL;
}
