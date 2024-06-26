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
