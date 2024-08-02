/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:49:03 by msennane          #+#    #+#             */
/*   Updated: 2024/08/01 13:28:15 by msennane         ###   ########.fr       */
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
		// Replace ft_printf with my own solution
		ft_printf("Usage: ./so_long map.ber\n");
		return (0);
	}
	map_filename = argv[1];
	state->map.file_path = map_filename;
	// Replace strlen with my own function
	len = strlen(map_filename);
	// Lets check the file extension to determine if its valid or not
	if (len < 4 || ft_strcmp(map_filename + len - 4, ".ber") != 0)
	{
		// Replace ft_printf here too with my own ft_printf
		ft_printf("Error\nInvalid map file extension\n");
		// This is a simple check to see if the file is a .ber file
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
	if (!check_path_to_collectibles(state))
	{
		return (0);
	}
	return (1);
}

void	cleanup_game_resources(t_game_state *state)
{
	int	i;

	// Destroy image assets
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
	// Time to destry player assets
	i = 0;
	while (i < 4)
	{
		if (state->player.curr_animation[i])
			mlx_destroy_image(state->mlx_instance,
				state->player.curr_animation[i]);
		// added animation to be destroyed too
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (state->player.spirites[i])
			mlx_destroy_image(state->mlx_instance, state->player.spirites[i]);
		i++;
	}
	mlx_destroy_window(state->mlx_instance, state->window_instance);
	mlx_destroy_display(state->mlx_instance);
	free(state->mlx_instance); // To be checked later for potential memory leaks
								// or double free
	free_map_layout(&state->map);
}
