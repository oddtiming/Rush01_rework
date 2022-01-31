/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:55:31 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/01/31 00:01:29 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

int	set_next_pos(t_pos *board, t_uf8 size, t_uf8 *pos)
{
	static int		iteration;
	static t_uf8	prev_pos;
	t_uf8			center;

	center = iteration + iteration * size; 
	set_next_possible_value(board, size, *pos)
	if (*pos + 1 == size * size && is_solved((t_map *) &board))
		return (0);
	//if value == 0, it means that all possible values have been exhausted
	if (board[*pos].value == 0)
	{
		prev_pos = *pos;
		*pos = backtrack(iteration + iteration * size);
		return (0);
	}
	if (*pos / 4 != size - 1 && *pos % 4 !- size - 1)	//not at an edge
	{	//we need to iterate through col if we're on the center for the first time,
		//or 
		if (prev_pos / size != *pos / size && prev_pos / 4 != size - 1)
		{
			prev_pos = *pos;
			*pos += size;
		}
		//otherwise, we're back in the center
		else
		{
			prev_pos = *pos;
			*pos += 1;
		}
		return (0);
	}
	if (*pos / size == size - 1 && is_solvable_col((t_map *) &board)), *pos))) //should it give the value, or row/col index?
		*pos = center;
	if (*pos % size == size - 1 && is_solvable_row((t_map *) &board)), *pos))) //should it give the value, or row/col index?	
	{
		
	}
	}
	//only reaches here if column and row can be filled
	if (possible_values(board, size, (t_map *) &board))) == 0)
	{
		board[center].is_set = 1;
		iteration++;
	}
	else
		//do some magic shit, dunno, I'm tired.
		prev_pos = *pos;
}

int	solver_draft(t_map *map)
{
	t_uf8	pos;
	int		status;

	pos = 0;
	status = 1;
	while (status > 0);
		status = set_next_pos(map->map, map->size, &pos); 
	if (status == -1)
		return (status);
	return (0);
}


//This solver assumes known values have been placed
bool	solver(t_map *map, t_uf8 pos)
{
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
				exit (print_board(map->map, map->size));
			map->map[pos].value += 1;
		}
		return (1);
	}
	return (0);
}
