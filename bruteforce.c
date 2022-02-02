/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bruteforce.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:54:55 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/02 12:15:10 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

bool	check_cols_for_duplicates(t_pos *board, uid_t size)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			k = j;
			while (++k < map
				if (board[i + k * size].value \
					== board[i + j * size].value)
					return (1);
			j++;
		}
		i++;
	}
	return (0);
}

bool	check_rows_for_duplicates(t_pos *board, uid_t size)
{
	int		i;
	int		j;
	int		k;

	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			k = i;
			while (++k < size)
				if (board[j * size + k].value \
					== board[j * size + i].value)
					return (1);
			i++;
		}
		j++;
	}
	return (0);
}

bool	there_are_duplicates(t_pos *board, uid_t size)
{
	return (check_cols_for_duplicates(board, size) | check_rows_for_duplicates(board, size));
}



bool	simple_bruteforce(t_pos *board, uid_t *views, uid_t size, uid_t pos, uid_t value)
{
	while (++value <= size)
	{
		if (!board[pos].is_set)
			board[pos].value = value;
		if (pos == size * size - 1 && is_solved(board, views, size))
			return (print_board(board, size));
		else if (pos != size * size - 1)
			simple_bruteforce(board, views, size, pos + 1, 0);
	}
	return (NO_SOLUTIONS);
}
