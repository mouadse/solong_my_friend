#include "mlx/mlx.h"
#include "so_long.h"
#include <stdio.h>

int ft_strcmp(const char *str1, const char *str2) {
  int i;

  i = 0;
  while (str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0')
    i++;
  return (str1[i] - str2[i]);
}

int validate_command_line_arguments(int argc, char **argv,
                                    t_game_state *state) {
  int len;
  char *map_filename;

  if (argc != 2) {
    // Replace printf with my own solution
    printf("Error: invalid usage\nUsage: %s [map_file.ber]\n", argv[0]);
    return (0);
  }
  map_filename = argv[1];
  state->map.file_path = map_filename;
  // Replace strlen with my own function
  len = strlen(map_filename);
  // Lets check the file extension to determine if its valid or not
  if (len < 4 || ft_strcmp(map_filename + len - 4, ".ber") != 0) {
    // Replace printf here too with my own printf
    printf("Invalid map file. It should be a .ber file\n");
    // This is a simple check to see if the file is a .ber file
    return (0);
  }
  return (1);
}

int process_arguments_and_map(int argc, char **argv, t_game_state *state) {

  // initialize_map(&state->map);
  // if (!validate_command_line_arguments(argc, argv, state))
  //   return (0);
  // if (!load_and_parse_map(state))
  //   return (0);
  // This part in our codebase is not yet implemented
  return (1);
}

void cleanup_game_resources(t_game_state *state) {
  // Destroy image assets
  int i;
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
  if (state->player.curr_animation)
    mlx_destroy_image(state->mlx_instance, state->player.curr_animation);
  i = 0;
  while (i < 4) {
    if (state->player.spirites[i])
      mlx_destroy_image(state->mlx_instance, state->player.spirites[i]);
    i++;
  }
  mlx_destroy_window(state->mlx_instance, state->window_instance);
  free(state->mlx_instance); // To be checked later for potential memory leaks
                             // or double free
  free_map_layout(&state->map);
}
