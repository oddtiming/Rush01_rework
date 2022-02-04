/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:57:48 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/04 00:21:33 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

void	print_views(int *views)
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

bool	print_board(int *board)
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
	//RO REMOVE
	exit (0);
	//END OF REMOVE

	// return (0);
}

int	fill_n_bits(int value)
{
	int	possible_values_bitwise;

	possible_values_bitwise = 0;
	while (++value <= g_size)
		possible_values_bitwise |= 1 << value;
	//TO REMOVE
	printf("possible values for %d are: ", value);
	while (1 & (value) >> value)
	{
		printf("%d ");
		value--;
	}
	printf("\n");
	//END OF REMOVE
	return (possible_values_bitwise)
}

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	exp(int base, int e)
{
	if (base == 0 && e < 0)
		return (0);
	else if (e == 0 || base == 1)
		return (1);
	return (base * exp(e - 1));
}
