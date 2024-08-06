/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:11:38 by msennane          #+#    #+#             */
/*   Updated: 2024/08/05 23:31:06 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/ft_printf.h"
#include "so_long.h"

void init_player_images(t_game_state *state) {
  int width;
  int height;

  state->player.moves_count = 0;
  state->player.score = 0;
  state->game_completed = 0;
  state->player.facing_direction = 3;
  state->player.spirites[0] = mlx_xpm_file_to_image(
      state->mlx_instance, "./assets/xpm/wa-p0.xpm", &width, &height);
  state->player.spirites[1] = mlx_xpm_file_to_image(
      state->mlx_instance, "./assets/xpm/wa-p1.xpm", &width, &height);
  state->player.spirites[2] = mlx_xpm_file_to_image(
      state->mlx_instance, "./assets/xpm/wa-p2.xpm", &width, &height);
  state->player.spirites[3] = mlx_xpm_file_to_image(
      state->mlx_instance, "./assets/xpm/wa-p3.xpm", &width, &height);
}

void display_moves_onscreen(t_game_state *state) {
  char *moves_str;
  char *display_str;

  moves_str = ft_itoa(state->player.moves_count);
  if (!moves_str)
    return;

  display_str = ft_strjoin("Moves: ", moves_str);
  if (display_str) {
    // Set larger font size (if your MLX version supports it)
    // mlx_set_font(state->mlx_instance, state->window_instance, "Arial", 20);

    mlx_string_put(state->mlx_instance, state->window_instance, 16, 20,
                   0x00FFFFFF, display_str);

    free(display_str);
  }

  free(moves_str);
}

void render_player(t_game_state *state) {
  mlx_put_image_to_window(
      state->mlx_instance, state->window_instance,
      state->player.spirites[state->player.facing_direction],
      state->player.col * 32, state->player.row * 32);
  display_moves_onscreen(state);
}

void find_positions(t_game_state *state) {
  int i;
  int j;

  i = 0;
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
  state->map.exit_position.col = state->level_exit.col;
  state->map.exit_position.row = state->level_exit.row;
}
