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

int	print_board(int *board)
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
	return (0);
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
		printf("%d ", value);
		value--;
	}
	printf("\n");
	//END OF REMOVE
	return (possible_values_bitwise);
}

int	smallest_bit(int nb)
{
	int i;

	//the second condition is an extra protection in case I set 1 << 0 by mistake
	if (!nb || nb >> 1)
		return (0);
	i = 1;
	while (1 >> i != 0x1)
		i++;
	return (i);
}

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_exp(int base, int e)
{
	if (base == 0 || e < 0)
		return (0);
	else if (e == 0 || base == 1)
		return (1);
	return (base * ft_exp(base, e - 1));
}

void	ft_putchar(int c)
{
	write(1, &c, 1);
	return ;
}
