#include "rush01.h"

static void	print_body(int *views, int *board, int *dimensions, int line_pos)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (i < dimensions[1])
	{
		if (i == dimensions[1] / 2 - 1 || dimensions[1] == 1)
			ft_putchar(views[line_pos + (2 * g_size)] + '0');
		else 
			write(1, " ", 1);
		j = 0;
		while (j < g_size)
		{
			write(1, "|", 1);
			k = 0;
			while (k < dimensions[0])
			{
				if (board[j + line_pos * g_size] & 1 << (k + 1 + (i * dimensions[1])))
					ft_putchar(k + 1 + (i * dimensions[0]) + '0');
				else
					ft_putchar('.');
				k++;
				if (k < dimensions[0])
					ft_putchar(' ');
			}
			j++;
		}
		write(1, "|", 1);
		if (i == dimensions[1] / 2 - 1 || dimensions[1] == 1)
			ft_putchar(views[line_pos + (3 * g_size)] + '0');
		else 
			write(1, " ", 1);
		write(1, "\n", 1);
		i++;
	}
}

static void	print_separator(int width)
{
	int	i;
	int	j;
	int	box_len;

	i = 0;
	box_len = width * 2 - 1;
	write(1, "-", 1);
	while (i < g_size)
	{
		write(1, "+", 1);
		j = 0;
		while (++j <= box_len)
			write(1, "-", 1);
		i++;
	}
	write(1, "+", 1);
	write(1, "-", 1);
	write(1, "\n", 1);
	return ;
}

static void	print_extremities(int *views, int width)
{
	int 	i;
	int 	j;
	int		box_len;

	i = 0;
	box_len = width * 2 - 1;
	write(1, "*", 1);
	while (i < g_size)
	{
		write(1, "|", 1);
		j = 0;
		while (++j <= box_len / 2)
			write(1, " ", 1);
		ft_putchar(views[i] + '0');
		while (++j <= box_len)
			write(1, " ", 1);
		i++;
	}
	write(1, "|", 1);
	write(1, "*", 1);
	write(1, "\n", 1);
}

int	*calc_box_dimensions(void)
{
	int	*dimensions;
	int	width;
	int	height;

	dimensions = malloc(2 * sizeof(int));
	if (!dimensions)
	{
		dimensions = NULL;
		return (dimensions);
	}
	width = 1;
	if (g_size == 2 || g_size == 4)
		width = 2;
	else if (g_size > 1)
		width = 3;
	height = (g_size - 1) / 3 + 1;
	dimensions[0] = width;
	dimensions[1] = height;
	return (dimensions);
}

void	print_possible_values(int *possible_values)
{
	int	line_pos;
	int	*box_dimensions;
	int	*views;

	views = get_views(views);
	if (!views)
		return ;
	line_pos = 0;
	box_dimensions = calc_box_dimensions();
	print_extremities(views + (0 * g_size), box_dimensions[0]);
	while (line_pos < g_size)
	{
		print_separator(box_dimensions[0]);
		print_body(views, possible_values, box_dimensions, line_pos);
		line_pos++;
	}
	print_separator(box_dimensions[0]);
	print_extremities(views + (1 * g_size), box_dimensions[0]);
	free (box_dimensions);
	return ;
}
