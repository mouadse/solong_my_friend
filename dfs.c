/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:44:52 by msennane          #+#    #+#             */
/*   Updated: 2024/07/29 16:47:27 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#define VISITED 1
#define NOT_VISITED 0

void	flood_fill(t_game_map *map, int col, int row, char **visited)
{
	if (map == NULL || col < 0 || col >= map->cols || row < 0
		|| row >= map->rows)
	{
		return ;
	}
	if (visited[row][col] == VISITED || map->layout[row][col] == '1')
	{
		return ;
	}
	visited[row][col] = VISITED;
	flood_fill(map, col - 1, row, visited);
	flood_fill(map, col + 1, row, visited);
	flood_fill(map, col, row - 1, visited);
	flood_fill(map, col, row + 1, visited);
}

int	has_valid_path(t_game_state *params)
{
	char	**visited;
	int		valid;

	if (params == NULL)
	{
		return (0);
	}
	visited = allocate_visited_array(params->map.rows, params->map.cols);
	if (visited == NULL)
	{
		return (0);
	}
	initialize_visited_array(visited, params->map.rows, params->map.cols);
	flood_fill(&params->map, params->player.col, params->player.row, visited);
	valid = visited[params->map.exit_position.row][params->map.exit_position.col] == VISITED;
	free_visited_array(visited, params->map.rows);
	if (!valid)
	{
		printf("Error: No path to collectibles\n");
	}
	return (valid);
}

char	**allocate_visited_array(int rows, int cols)
{
	char	**visited;

	visited = malloc(rows * sizeof(char *));
	if (visited == NULL)
	{
		return (NULL);
	}
	for (int i = 0; i < rows; i++)
	{
		visited[i] = malloc(cols * sizeof(char));
		if (visited[i] == NULL)
		{
			free_visited_array(visited, i);
			return (NULL);
		}
	}
	return (visited);
}

void	initialize_visited_array(char **visited, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			visited[i][j] = NOT_VISITED;
		}
	}
}

void	free_visited_array(char **visited, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		free(visited[i]);
	}
	free(visited);
}
