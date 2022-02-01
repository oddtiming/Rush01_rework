# include "rush01.h"

void	modify_board(t_map *map)
{
	t_pos	*new_board;
	int		i;

	i = 0;
	new_board = malloc((map->size * map->size+ 1) * sizeof(t_pos));
	if (!new_board)
		return ;
	new_board[0].value = map->size;
	while (i < map->size * map->size)
	{
		new_board[i + 1] = map->map[i];
		i++;
	}
	free (map->map);
	map->map = new_board + 1;
	return ;
}
