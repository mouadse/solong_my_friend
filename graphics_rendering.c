#include "so_long.h"

void load_game_textures(t_game_state *state) {
  int width;
  int height;

  state->assets.wall_asset = mlx_xpm_file_to_image(
      state->mlx_instance, "./assets/xpm/wall.xpm", &width, &height);
  state->assets.coin_asset = mlx_xpm_file_to_image(
      state->mlx_instance, "./assets/xpm/coin.xpm", &width, &height);
  state->assets.floor_asset = mlx_xpm_file_to_image(
      state->mlx_instance, "./assets/xpm/floor.xpm", &width, &height);
  state->assets.open_door_asset = mlx_xpm_file_to_image(
      state->mlx_instance, "./assets/xpm/open_door.xpm", &width, &height);
  state->assets.closed_door_asset = mlx_xpm_file_to_image(
      state->mlx_instance, "./assets/xpm/closed_door.xpm", &width, &height);
}

void render_map_tile(t_game_state *state, int y, int x) {
  int asset_size = 32; // assuming 32x32 pixel assets
  if (state->map.layout[x][y] == '1')
    mlx_put_image_to_window(state->mlx_instance, state->window_instance,
                            state->assets.wall_asset, x * asset_size,
                            y * asset_size);
  else if (state->map.layout[x][y] == '0')
    mlx_put_image_to_window(state->mlx_instance, state->window_instance,
                            state->assets.floor_asset, x * asset_size,
                            y * asset_size);
  else if (state->map.layout[x][y] == 'C')
    mlx_put_image_to_window(state->mlx_instance, state->window_instance,
                            state->assets.coin_asset, x * asset_size,
                            y * asset_size);
  else if (state->map.layout[x][y] == 'E') {
    if (state->game_completed)
      mlx_put_image_to_window(state->mlx_instance, state->window_instance,
                              state->assets.open_door_asset, x * asset_size,
                              y * asset_size);
    else
      mlx_put_image_to_window(state->mlx_instance, state->window_instance,
                              state->assets.closed_door_asset, x * asset_size,
                              y * asset_size);
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
      !state->assets.open_door_asset || !state->player.curr_animation[0] ||
      !state->player.curr_animation[1] || !state->player.curr_animation[2] ||
      !state->player.curr_animation[3] || !state->player.spirites[0] ||
      !state->player.spirites[1] || !state->player.spirites[2] ||
      !state->player.spirites[3]) {
    printf("Error loading textures\n");
    // add free and detroy functions here
    exit(1);
  }
}
