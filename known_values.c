#include "rush01.h"

static bool place_top(t_map *map)
{
	uint8_t	i;
	uint8_t	j;

	printf("in place_top, map->size = %d\n", map->size);
	i = 0;
	while (i < map->size)
	{
		if (map->top_view[i] == 1)
		{
	printf("place_top found that map->top_view[%d] == 1\n", i);
			map->map[i].value = map->size;
			map->map[i].is_set = true;
		}
		else if (map->top_view[i] == map->size)
		{
			j = 0;
			while (++j <= map->size)
			{
			map->map[(j - 1) * map->size + i].value = j;
			map->map[(j - 1) * map->size + i].is_set = true;
			}
		}
		i++;
	}
	return (0);
}

static bool place_bottom(t_map *map)
{
	uint8_t	i;
	uint8_t	j;

	i = 0;
	while (i < map->size)
	{
		if (map->bottom_view[i] == 1)
		{
			map->map[(map->size - 1) * map->size + i].value = map->size;
			map->map[(map->size - 1) * map->size + i].is_set = true;
		}
		else if (map->bottom_view[i] == map->size)
		{
			j = 0;
			while (++j <= map->size)
			{
			map->map[(map->size - j) * map->size + i].value = j;
			map->map[(map->size - j) * map->size + i].is_set = true;
			}
		}
		i++;
	}
	return (0);
}

static bool place_left(t_map *map)
{
	uint8_t	i;
	uint8_t	j;

	i = 0;
	while (i < map->size)
	{
		if (map->left_view[i] == 1)
		{
			map->map[i * map->size].value = map->size;
			map->map[i * map->size].is_set = true;
		}
		else if (map->left_view[i] == map->size)
		{
			j = 0;
			while (++j <= map->size)
			{
			map->map[i * map->size + (j - 1)].value = j;
			map->map[i * map->size + (j - 1)].is_set = true;
			}
		}

		i++;
	}
	return (0);
}

static bool place_right(t_map *map)
{
	uint8_t	i;
	uint8_t	j;

	i = 0;
	while (i < map->size)
	{
		if (map->right_view[i] == 1)
		{
			map->map[i * map->size + (map->size - 1)].value = map->size;
			map->map[i * map->size + (map->size - 1)].is_set = true;
		}
		else if (map->right_view[i] == map->size)
		{
			j = 0;
			while (++j <= map->size)
			{
				map->map[i * map->size + (map->size - j)].value = j;
				map->map[i * map->size + (map->size - j)].is_set = true;
			}
		}

		i++;
	}
	return (0);
}

bool	place_known_values(t_map *map)
{
	if (place_top(map))
		return (1);
	if (place_bottom(map))
		return (1);
	if (place_left(map))
		return (1);
	if (place_right(map))
		return (1);
	
	return (0);
}