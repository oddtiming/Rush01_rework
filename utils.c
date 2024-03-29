#include "rush01.h"

void	unset_bit(int *i, int b)
{
	*i &= ~(1 << b);
}

int	at(int x, int y)
{
	return (x + g_size * y);
}

int	smallest_bit(int nb)
{
	int i;

	if (!nb || nb & (1 << 0))
		return (0);
	i = 1;
	while (((1 << i) & nb) == 0 && i <= g_size)
		i++;
	return (i);
}

int	largest_bit(int nb)
{
	int i;

	if (!nb || nb & (1 << 0))
		return (0);
	i = g_size;
	while (((1 << i) & nb) == 0 && i > 0)
		i--;
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

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	err_msg(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (EXIT_FAILURE);
}

void	*ft_calloc(size_t sz)
{
	char	*mem;
	size_t	i;

	mem = malloc(sz);
	if (!mem)
		return (NULL);
	i = 0;
	while (i < sz)
		mem[i++] = 0;
	return (mem);
}
