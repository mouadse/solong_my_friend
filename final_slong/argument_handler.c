/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:49:03 by msennane          #+#    #+#             */
/*   Updated: 2024/08/05 22:41:32 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <X11/X.h>

int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0')
		i++;
	return (str1[i] - str2[i]);
}

int	validate_command_line_arguments(int argc, char **argv, t_game_state *state)
{
	int		len;
	char	*map_filename;

	if (argc != 2)
	{
		ft_printf("Usage: ./so_long map.ber\n");
		return (0);
	}
	map_filename = argv[1];
	state->map.file_path = map_filename;
	len = ft_strlen(map_filename);
	if (len < 4 || ft_strcmp(map_filename + len - 4, ".ber") != 0)
	{
		ft_printf("Error\nInvalid map file extension\n");
		return (0);
	}
	return (1);
}

int	process_arguments_and_map(int argc, char **argv, t_game_state *state)
{
	initialize_map(&state->map);
	if (!validate_command_line_arguments(argc, argv, state))
	{
		return (0);
	}
	if (!load_and_parse_map(state))
	{
		return (0);
	}
	if (!validate_map(&state->map))
	{
		return (0);
	}
	if (!check_map_surrounded_by_walls(&state->map))
		return (0);
	state->map.total_collectibles = count_collectibles(&state->map);
	find_positions(state);
	if (!check_path_to_collectibles(state))
	{
		return (0);
	}
	return (1);
}

void	cleanup_game_resources(t_game_state *state)
{
	int	i;

	if (state->assets.wall_asset)
		mlx_destroy_image(state->mlx_instance, state->assets.wall_asset);
	if (state->assets.coin_asset)
		mlx_destroy_image(state->mlx_instance, state->assets.coin_asset);
	if (state->assets.open_door_asset)
		mlx_destroy_image(state->mlx_instance, state->assets.open_door_asset);
	if (state->assets.floor_asset)
		mlx_destroy_image(state->mlx_instance, state->assets.floor_asset);
	if (state->assets.closed_door_asset)
		mlx_destroy_image(state->mlx_instance, state->assets.closed_door_asset);
	i = 0;
	while (i < 4)
	{
		if (state->player.spirites[i])
			mlx_destroy_image(state->mlx_instance, state->player.spirites[i]);
		i++;
	}
	mlx_destroy_window(state->mlx_instance, state->window_instance);
	mlx_destroy_display(state->mlx_instance);
	free(state->mlx_instance);
	free_map_layout(&state->map);
}
