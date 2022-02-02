/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:55:31 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/01 20:15:27 by iyahoui-         ###   ########.fr       */
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
// t_uf8	set_next_pos
// --> 3 possible options:
                    // 1) go right
                    // 2) go down
                    // 3) go to next "iteration": {0, 0}->{1, 1} -> {2, 2} ...
//Following this, the t-search pattern should start with ROWS
//Could maybe try a 

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
		size = (board - 1)->value;
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

//STOPPED HERE, need to work on this rework, because the previous one does not work, clearly.
t_uf8	set_next_value_v2(t_pos *board, t_uf8 pos, t_uf8 size)
{
	static t_uf16	*possible_values;
	t_uf8			i;

	if (board[pos].is_set)
		return (board[pos].value);
	if (!possible_values)
		fill_values;
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
		size = (board - 1)->value;
	if (pos == size * size && is_solved((t_map *)(&board)))
		return (print_board(board, size));
	board[pos].value = set_next_value(board, pos);
	while (board[pos].value)
	{
		if (pos % size >= pos / size && pos != size * size - 1) //meaning y >= x
		{
			if (pos % size != size - 1)
				return (solver_recursive(board, pos + 1)); //move right
			else
				return (solver_recursive(board, (pos/size) + size * (pos/size - 1)));
		}
		else if (pos != size * size - 1)	//meaning y < x, but not last_board_pos
		{
			if (pos / size != size - 1)
				return (solver_recursive(board, pos + size));
			else
				return (solver_recursive(board, (pos % size + 1) + size * (pos % size + 1)));
		}
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
