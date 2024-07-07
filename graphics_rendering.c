#include "so_long.h"

void load_game_textures(t_game_state *state) {
  int width;
  int height;

  state->assets.wall_asset = mlx_xpm_file_to_image(
      state->mlx_instance, "./textures/images/wall.xpm", &width, &height);
  state->assets.coin_asset = mlx_xpm_file_to_image(
      state->mlx_instance, "./textures/images/collectible.xpm", &width,
      &height);
  state->assets.floor_asset = mlx_xpm_file_to_image(
      state->mlx_instance, "./textures/images/empty.xpm", &width, &height);
  state->assets.open_door_asset = mlx_xpm_file_to_image(
      state->mlx_instance, "./textures/images/exit1.xpm", &width, &height);
  state->assets.closed_door_asset = mlx_xpm_file_to_image(
      state->mlx_instance, "./textures/images/exit2.xpm", &width, &height);
}

void render_map_tile(t_game_state *state, int y, int x) {
  if (state->map.layout[x][y] == '1')
    mlx_put_image_to_window(state->mlx_instance, state->window_instance,
                            state->assets.wall_asset, x, y);
  else if (state->map.layout[x][y] == '0')
    mlx_put_image_to_window(state->mlx_instance, state->window_instance,
                            state->assets.floor_asset, x, y);
  else if (state->map.layout[x][y] == 'C')
    mlx_put_image_to_window(state->mlx_instance, state->window_instance,
                            state->assets.coin_asset, x, y);
  else if (state->map.layout[x][y] == 'E') {
    if (state->game_completed)
      mlx_put_image_to_window(state->mlx_instance, state->window_instance,
                              state->assets.open_door_asset, x, y);
    else
      mlx_put_image_to_window(state->mlx_instance, state->window_instance,
                              state->assets.closed_door_asset, x, y);
  }
}

void render_game_map(t_game_state *state) {
  int i;
  int j;

  i = 0;
  while (i < state->map.rows) {
    j = 0;
    while (j < state->map.cols) {
      render_map_tile(state, j, i);
      j++;
    }
    i++;
  }
}

void verify_textures_loaded(t_game_state *state) {
  if (!state->assets.wall_asset || !state->assets.coin_asset ||
      !state->assets.floor_asset || !state->assets.closed_door_asset ||
      !state->assets.open_door_asset || !state->player.curr_animation ||
      !state->player.spirites[0] || !state->player.spirites[1] ||
      !state->player.spirites[2] || !state->player.spirites[3]) {
    printf("Error\n❌ Failed to load one or more images. ❌ \n");
    // free_and_destroy(params);
    // call free and destroy later
    exit(1);
  }
}
