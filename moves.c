#include "so_long.h"

int valid_move(t_game_state *game_options, int row, int col) {
  if (row < 0 || row > game_options->map.rows - 1 || col < 0 ||
      col > game_options->map.cols - 1)
    return (0);
  if (game_options->map.layout[row][col] == '1')
    return (0);
  return (1);
}
