/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:44:52 by msennane          #+#    #+#             */
/*   Updated: 2024/08/01 13:12:53 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(t_game_map *map, int col, int row, char **visited,
		bool is_exit_open)
{
	if (col < 0 || col >= map->cols || row < 0 || row >= map->rows)
		return ;
	if (map->layout[row][col] == '1' || visited[row][col] == '1')
		return ;
	if (map->layout[row][col] == 'E' && !is_exit_open)
		return ;
	visited[row][col] = '1';
	flood_fill(map, col + 1, row, visited, is_exit_open);
	flood_fill(map, col - 1, row, visited, is_exit_open);
	flood_fill(map, col, row + 1, visited, is_exit_open);
	flood_fill(map, col, row - 1, visited, is_exit_open);
}

int	has_valid_path(t_game_state *params, bool is_exit_open)
{
	char	**visited;
	int		collectibles_found;
	bool	exit_found;

	int i, j;
	collectibles_found = 0;
	exit_found = false;
	visited = (char **)malloc(params->map.rows * sizeof(char *));
	if (!visited)
		return (0);
	for (i = 0; i < params->map.rows; i++)
	{
		visited[i] = (char *)malloc(params->map.cols * sizeof(char));
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			return (0);
		}
		for (j = 0; j < params->map.cols; j++)
			visited[i][j] = '0';
	}
	flood_fill(&params->map, params->player.col, params->player.row, visited,
		is_exit_open);
	// Check if all collectibles and exit (if open) are reachable
	for (i = 0; i < params->map.rows; i++)
	{
		for (j = 0; j < params->map.cols; j++)
		{
			if (params->map.layout[i][j] == 'C' && visited[i][j] == '1')
			{
				collectibles_found++;
			}
			else if (params->map.layout[i][j] == 'E' && visited[i][j] == '1')
			{
				exit_found = true;
			}
		}
	}
	for (i = 0; i < params->map.rows; i++)
		free(visited[i]);
	free(visited);
	// Check if all collectibles are reachable and the exit is reachable if it's open
	return (collectibles_found == params->map.total_collectibles)
		&& (!is_exit_open || exit_found);
}
