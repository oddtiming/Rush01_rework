/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:57:48 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/03 18:02:55 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

void	print_views(uid_t *views)
{
	int		i;
	char	c;

	i = 0;
	write(1, " view\n", sizeof(" view\n"));
	while (i < g_size * 4)
	{
		c = views[i] + '0';
		write (1, &c, 1);
		if ((i + 1) % g_size)
			write (1, " ", 1);
		else
			write (1, "\n", 1);
		i++;
	}
	return ;
}

bool	print_board(uid_t *board)
{
	int		i;
	char	c;

	i = 0;
	while (i < g_size * g_size)
	{
		c = board[i] + '0';
		write (1, &c, 1);
		if ((i + 1) % g_size)
			write (1, " ", 1);
		else
			write(1, "\n", 1);
		i++;
	}
	exit (0);

	// return (0);
}

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}
