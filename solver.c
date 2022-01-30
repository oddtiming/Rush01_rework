#include "rush01.h"

//This solver assumes known values have been placed
bool	solver(t_map *map, uint8_t pos)
{
	// printf("entered solver with pos = %d\n", pos);
	if (pos < (map->size * map->size - 1))
	{
		while (map->map[pos].is_set)
			pos++;
		map->map[pos].value = 1;
		while (map->map[pos].value <= map->size)
		{
			solver(map, pos + 1);
			map->map[pos].value += 1;
		}
	}
	else
	{
		map->map[pos].value = 1;
		while (map->map[pos].value <= map->size)
		{
			if (is_solved(map))
			{
				print_board(map->map, map->size);
				// printf("board is solved!\n");
				return (0);
			}
			map->map[pos].value += 1;
		}
		return (1);
	}
	return(0);
}