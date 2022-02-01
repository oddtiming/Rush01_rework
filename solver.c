/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:55:31 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/01 13:10:44 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"


//	Basically the 4 possibilities are :
//	backtrack:		- has no more possible values;
//						curr_value == 0;
//	pos += 1: 		- is center after col has been solved;
//						prev_pos % size == curr_pos % size;
//						prev_pos / size == size - 1; <--this one if before evaluating prev_pos % size == curr_pos % size
//					- is moving right;
//						prev_pos == curr_pos - 1;
//	pos += size:	- is center for the first time; 
//						prev_pos < curr_pos;
//				    - is moving down;
//						prev_pos % size == curr_pos % size;
//	do nothing:		- is last position
/**
 * @brief Set the next pos object
 * 			could call moves such as 
 * 				(void)	(moves[4])(t_board *, t_uf8 *) { move_left, move_right, ...};
 * 			or even better a
 * 			move(*pos, "left");
 * 			move(*pos, "right");
 * 			so that I could use a last_move;
 * 			a recursive approach would be better though, since last_move
 * 		
 * 
 * @param board 
 * @param size 
 * @param pos 
 * @return int 
 */
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


// t_uf8	set_next_pos
// --> 3 possible options:
                    // 1) go right
                    // 2) go down
                    // 3) go to next "iteration": {0, 0}->{1, 1} -> {2, 2} ...
//Following this, the t-search pattern should start with ROWS
//Could maybe try a 
#define xy(X, Y)	

t_uf16	smallest_bit(t_uf16 bitwise)
{
	t_uf16	i;

	i = 0;
	while (++i < 15)
		if (bitwise >> i & 0x1)
			return (i);
	return (0);
}

t_uf8	set_next_value(t_pos *board, t_uf8 pos)
{
	static t_uf8	size;
	t_uf16			bitwise_values;
	t_uf8			i;

	if (board[pos].is_set)
		return (board[pos].value);
	if (!size)
		size = *(board - 1);
	i = 0;
	while (++i <= size)
		bitwise_values |= 1 << i;	//to set the bit
	i = 0;
	if (pos >= size)
		i = pos - size;
	while (i / size)
	{
		bitwise_values &= ~(1 << board[pos - size * i].value); //to unset the bit
		i -= size;
	}
	i = pos;
	while (--i % pos)
		bitwise_values &= ~(1 << board[pos - i].value); //to unset the bit
	return (smallest_bit(bitwise_values));
}

bool	solver_recursive(t_pos *board, t_uf8 pos)
{
	static t_uf8	size;

	if (!size)
		size = *(board - 1);
	if (pos == size * size && is_solved((t_map *)(&board))
		return (print_board((t_map *)(&board), size));
	board[pos].value = set_next_value(board, pos);
	while (board[pos].value )
	{
		if (pos % size < pos / size) //meaning x > y
			return (solver_recursive(board, pos + size)) //move right
		else if (pos != size * size - 1)	//meaning y <= x, but not last_board_pos
			return (solver_recursive(board, pos + 1))
	}
	return (1);
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
