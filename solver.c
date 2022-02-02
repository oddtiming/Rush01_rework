#include "rush01.h"

//This solver assumes known values have been placed
bool	solver(t_map *map, uid_t pos)
{
	if (pos < (map->size * map->size - 1))
	{
		while (map->board[pos].is_set)
			pos++;
		map->board[pos].value = 1;
		while (map->board[pos].value <= map->size)
		{
			solver(map, pos + 1);
			map->board[pos].value += 1;
		}
	}
	else
	{
		map->board[pos].value = 1;
		while (map->board[pos].value <= map->size)
		{
			if (is_solved(map->board, map->views, map->size))
				exit (print_board(map->board, map->size));
			map->board[pos].value += 1;
		}
		return (1);
	}
	return (0);
}
