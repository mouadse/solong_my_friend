/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:49:48 by msennane          #+#    #+#             */
/*   Updated: 2024/07/29 16:49:49 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_2d_position(int position[2], int x, int y)
{
	position[0] = x;
	position[1] = y;
}

int	**create_visited_positions_tracker(t_game_state *state)
{
	int	i;
	int	**tracker;

	tracker = malloc(sizeof(int *) * state->map.cols * state->map.rows);
	if (!tracker)
		return (NULL);
	i = 0;
	while (i < state->map.cols * state->map.rows)
	{
		tracker[i] = malloc(sizeof(int) * 2);
		if (!tracker)
			return (NULL);
		i++;
	}
	return (tracker);
}

void	deallocate_visited_positions_tracker(t_game_state *state, int **tracker)
{
	int	i;

	i = 0;
	while (i < state->map.cols * state->map.rows)
	{
		free(tracker[i]);
		i++;
	}
	free(tracker);
}
