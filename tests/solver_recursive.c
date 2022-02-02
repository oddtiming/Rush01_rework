#include "rush01.h"

uid_t	smallest_bit(uid_t bitwise)
{
	uid_t	i;

	i = 0;
	while (++i < 15)
		if (bitwise >> i & 0x1)
			return (i);
	return (0);
}

uid_t	set_next_value(t_pos *board, uid_t pos)
{
	static uid_t	size;
	uid_t			bitwise_values;
	uid_t			i;

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
uid_t	set_next_value_v2(t_pos *board, uid_t pos, uid_t size)
{
	static uid_t	bitwise_values;
	uid_t			i;

	if (board[pos].is_set)
		return (board[pos].value);
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

bool	solver_recursive(t_pos *board, uid_t pos)
{
	static uid_t	size;

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