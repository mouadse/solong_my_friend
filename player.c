#include "mlx/mlx.h"
#include "so_long.h"

void initialize_and_load_player_images(t_game_state *state) {
  int width;
  int height;

  state->player.moves_count = 0;
  state->player.score = 0;
  state->game_completed = 0;
  state->player.facing_direction = 3;

  state->player.spirites[0] = mlx_xpm_file_to_image(
      state->mlx_instance, "./textures/player/pac_man0.xpm", &width, &height);
  state->player.spirites[1] = mlx_xpm_file_to_image(
      state->mlx_instance, "./textures/player/pac_man1.xpm", &width, &height);
  state->player.spirites[2] = mlx_xpm_file_to_image(
      state->mlx_instance, "./textures/player/pac_man2.xpm", &width, &height);
  state->player.spirites[3] = mlx_xpm_file_to_image(
      state->mlx_instance, "./textures/player/pac_man3.xpm", &width, &height);
  state->player.curr_animation = mlx_xpm_file_to_image(
      state->mlx_instance, "./textures/player/animation.xpm", &width, &height);
}

void render_player(t_game_state *state) {
  mlx_put_image_to_window(
      state->mlx_instance, state->window_instance,
      state->player.spirites[state->player.facing_direction],
      state->player.col * 32, state->player.row * 32);
}

void locate_player_and_exit_positions(t_game_state *state) {
  int i;
  int j;
  // This code should be refactored to be using while loop instead of for loop

  for (i = 0; i < state->map.rows; i++) {
    for (j = 0; j < state->map.cols; j++) {
      if (state->map.layout[i][j] == 'P') {
        state->player.col = j;
        state->player.row = i;
      } else if (state->map.layout[i][j] == 'E') {
        state->level_exit.col = j;
        state->level_exit.row = i;
      }
    }
  }

  // Set the target position to the exit position
  state->map.exit_position.col = state->level_exit.col;
  state->map.exit_position.row = state->level_exit.row;
}
