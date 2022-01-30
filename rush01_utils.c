/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:57:48 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/01/30 18:09:25 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

int	ft_sqrt(int nb)
{
	int	sqrt;

	if (nb <= 0)
		return (0);
	if (nb == 1)
		return (1);
	sqrt = nb / 2;
	while (nb / sqrt < sqrt)
	{
		if (4 * (nb / sqrt) < sqrt)
			sqrt /= 2;
		else
			sqrt--;
	}
	if (sqrt * sqrt == nb)
		return (sqrt);
	else
		return (0);
}

void	print_views(uint8_t *views, int map_size)
{
	int		i;
	char	c;

	i = 0;
	write(1, " view\n", sizeof(" view\n"));
	while (i < map_size * 4)
	{
		c = views[i] + '0';
		write (1, &c, 1);
		if ((i + 1) % map_size)
			write (1, " ", 1);
		else
			write (1, "\n", 1);
		i++;
	}
	return ;
}

bool	print_board(t_pos *map, uint8_t size)
{
	int		i;
	char	c;

	i = 0;
	while (i < size * size)
	{
		c = map[i].value + '0';
		write (1, &c, 1);
		if ((i + 1) % size)
			write (1, " ", 1);
		else
			write(1, "\n", 1);
		i++;
	}
	return (0);
}

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}
