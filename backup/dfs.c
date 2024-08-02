/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:44:52 by msennane          #+#    #+#             */
/*   Updated: 2024/08/01 23:14:03 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(t_game_map *map, int col, int row, char **visited)
{
	if (col < 0 || col >= map->cols || row < 0 || row >= map->rows)
		return ;
	if (map->layout[row][col] == '1' || visited[row][col] == '1')
		return ;
	if (map->layout[row][col] == 'E' && !map->flood_fill_exit)
		return ;
	visited[row][col] = '1';
	flood_fill(map, col + 1, row, visited);
	flood_fill(map, col - 1, row, visited);
	flood_fill(map, col, row + 1, visited);
	flood_fill(map, col, row - 1, visited);
}

void	free_visited_array(char **visited, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

char	**allocate_visited_array_two(t_game_state *params)
{
	char	**visited;
	int		i;
	int		j;

	visited = (char **)malloc(params->map.rows * sizeof(char *));
	if (!visited)
		return (NULL);
	i = 0;
	while (i < params->map.rows)
	{
		visited[i] = (char *)malloc(params->map.cols * sizeof(char));
		if (!visited[i])
		{
			free_visited_array(visited, i);
			return (NULL);
		}
		j = 0;
		while (j < params->map.cols)
		{
			visited[i][j] = '0';
			j++;
		}
		i++;
	}
	return (visited);
}

void	check_reachability(t_game_state *params, char **visited,
		int *collectibles_found, bool *exit_found)
{
	int	i;
	int	j;

	i = 0;
	while (i < params->map.rows)
	{
		j = 0;
		while (j < params->map.cols)
		{
			if (params->map.layout[i][j] == 'C' && visited[i][j] == '1')
				(*collectibles_found)++;
			else if (params->map.layout[i][j] == 'E' && visited[i][j] == '1')
				*exit_found = true;
			j++;
		}
		i++;
	}
}

int	has_valid_path(t_game_state *params)
{
	char	**visited;
	int		collectibles_found;
	bool	exit_found;

	collectibles_found = 0;
	exit_found = false;
	visited = allocate_visited_array_two(params);
	if (!visited)
		return (0);
	flood_fill(&params->map, params->player.col, params->player.row, visited);
	check_reachability(params, visited, &collectibles_found, &exit_found);
	free_visited_array(visited, params->map.rows);
	return (collectibles_found == params->map.total_collectibles
		&& (!params->map.flood_fill_exit || exit_found));
}
