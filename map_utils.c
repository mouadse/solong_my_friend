#include "so_long.h"

int	is_valid_map_character(char character)
{
	int			i;
	const char	valid_chars[] = {'0', '1', 'C', 'E', 'P'};

	i = 0;
	while (i < sizeof(valid_chars))
	{
		if (character == valid_chars[i])
			return (1);
		i++;
	}
	return (0);
}
