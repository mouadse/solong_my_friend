/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:50:21 by msennane          #+#    #+#             */
/*   Updated: 2024/07/30 00:42:49 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

int handle_keypress(int keycode, t_game_state *state) {
  printf("Keycode: %d\n", keycode);
  if (keycode == ESC_KEY) {
    cleanup_game_resources(state);
    exit(EXIT_SUCCESS);
  } else if (keycode == UP_KEY_W || keycode == UP_KEY_ARROW) {
    move_sprite_up(state);
  } else if (keycode == LEFT_KEY_A || keycode == LEFT_KEY_ARROW) {
    move_sprite_left(state);
  } else if (keycode == DOWN_KEY_S || keycode == DOWN_KEY_ARROW) {
    move_sprite_down(state);
  } else if (keycode == RIGHT_KEY_D || keycode == RIGHT_KEY_ARROW) {
    move_sprite_right(state);
  }
  return (0);
}

int handle_window_close(t_game_state *state) {
  cleanup_game_resources(state);
  exit(EXIT_SUCCESS);
}

int update_window(t_game_state *state) {
  if (state->game_completed && state->player.col == state->level_exit.col &&
      state->player.row == state->level_exit.row) {
    printf("Congratulations! You have completed the game!\n");
    cleanup_game_resources(state);
    exit(EXIT_SUCCESS);
  }
  mlx_clear_window(state->mlx_instance, state->window_instance);
  render_game_map(state);
  render_player(state);
  return (0);
}

int main(int argc, char **argv) {
  t_game_state state;

  if (process_arguments_and_map(argc, argv, &state)) {
    state.mlx_instance = mlx_init();
    state.window_instance =
        mlx_new_window(state.mlx_instance, state.map.cols * 32,
                       state.map.rows * 32, "so_long");
    initialize_and_load_player_images(&state);
    load_game_textures(&state);
    verify_textures_loaded(&state);
    mlx_hook(state.window_instance, KeyPress, KeyPressMask, handle_keypress,
             &state);
    // mlx_hook(state.window_instance, 2, 1L << 0, handle_keypress, &state);

    mlx_loop_hook(state.mlx_instance, update_window, &state);
    mlx_hook(state.window_instance, DestroyNotify, StructureNotifyMask, handle_window_close, &state);
    // mlx_hook(state.window_instance, 17, 1L << 17, handle_window_close,
    // &state);
    mlx_loop(state.mlx_instance);
  }
  free_map_layout(&state.map);
  return (EXIT_SUCCESS);
}
