/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:11:38 by msennane          #+#    #+#             */
/*   Updated: 2024/07/29 16:50:14 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void initialize_and_load_player_images(t_game_state *state) {
  int width;
  int height;

  state->player.moves_count = 0;
  state->player.score = 0;
  state->game_completed = 0;
  state->player.facing_direction = 3;

  state->player.spirites[0] = mlx_xpm_file_to_image(
      state->mlx_instance, "./assets/xpm/player_0.xpm", &width, &height);
  state->player.spirites[1] = mlx_xpm_file_to_image(
      state->mlx_instance, "./assets/xpm/player_1.xpm", &width, &height);
  state->player.spirites[2] = mlx_xpm_file_to_image(
      state->mlx_instance, "./assets/xpm/player_2.xpm", &width, &height);
  state->player.spirites[3] = mlx_xpm_file_to_image(
      state->mlx_instance, "./assets/xpm/player_3.xpm", &width, &height);
  state->player.curr_animation[0] = mlx_xpm_file_to_image(
      state->mlx_instance, "./assets/xpm/move_0.xpm", &width, &height);
  state->player.curr_animation[1] = mlx_xpm_file_to_image(
      state->mlx_instance, "./assets/xpm/move_1.xpm", &width, &height);
  state->player.curr_animation[2] = mlx_xpm_file_to_image(
      state->mlx_instance, "./assets/xpm/move_2.xpm", &width, &height);
  state->player.curr_animation[3] = mlx_xpm_file_to_image(
      state->mlx_instance, "./assets/xpm/move_3.xpm", &width, &height);
}

void render_player(t_game_state *state) {
  mlx_put_image_to_window(
      state->mlx_instance, state->window_instance,
      state->player.spirites[state->player.facing_direction],
      state->player.col * 32, state->player.row * 32);
}

void locate_player_and_exit_positions(t_game_state *state) {
  int i = 0;
  int j;

  while (i < state->map.rows) {
    j = 0;
    while (j < state->map.cols) {
      if (state->map.layout[i][j] == 'P') {
        state->player.col = j;
        state->player.row = i;
      } else if (state->map.layout[i][j] == 'E') {
        state->level_exit.col = j;
        state->level_exit.row = i;
      }
      j++;
    }
    i++;
  }

  // Set the target position to the exit position
  state->map.exit_position.col = state->level_exit.col;
  state->map.exit_position.row = state->level_exit.row;
}
