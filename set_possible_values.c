#include "rush01.h"

// void	remove_possible_values(int *possible_values, int x, int y, int bit_mask)
// {
// 	static int	*views;
// 	int			diff;

// 	if (!views)
// 		views = get_views(NULL);

// 	diff = views[x + 0 * g_size] - (y + 1);
// 	if (diff > 0) // Remove values for top views
// 		possible_values[x + y * g_size] &= (bit_mask >> (diff));
// 	// diff = (g_size - 1 - y) -  views[x + 1 * g_size];
// 	// if (diff > 0) // Remove values for top views
// 	// 	possible_values[x + y * g_size] &= (bit_mask >> (g_size - diff));
// 	// diff = x - views[y + 2 * g_size];
// 	// if (diff > 0) // Remove values for top views
// 	// 	possible_values[x + y * g_size] &= (bit_mask >> (g_size - diff));
// 	// diff = (g_size - 1 - x) - views[y + 3 * g_size];
// 	// if (diff > 0) // Remove values for top views
// 	// 	possible_values[x + y * g_size] &= (bit_mask >> (g_size - diff));
// }

void	remove_possible_values_at(int *possible_values, int x, int y, int bit_mask)
{
	static int	*views;
	int			diff;

	if (!views)
		views = get_views(NULL);

	diff = views[x + 0 * g_size] - (y + 1);
	if (diff > 0) // Remove values for top views
		possible_values[x + y * g_size] &= (bit_mask >> (diff));
	diff = views[x + 1 * g_size] - (g_size - y);
	if (diff > 0) // Remove values for top views
		possible_values[x + y * g_size] &= (bit_mask >> (diff));
	diff = views[y + 2 * g_size] - (x + 1);
	if (diff > 0) // Remove values for top views
		possible_values[x + y * g_size] &= (bit_mask >> (diff));
	diff = views[y + 3 * g_size] - (g_size - x);
	if (diff > 0) // Remove values for top views
		possible_values[x + y * g_size] &= (bit_mask >> (diff));
}

//removes duplicates
void	set_possible_values_at(int *board, int *possible_values, int x, int y)
{
	static int	bit_mask;
	int			at_x;
	int			at_y;
	int			pos;

	if (!bit_mask)
		bit_mask = ((ft_exp(2, g_size) - 1) << 1);
	at_x = g_size;
	at_y = g_size;
	pos = at(x, y);
	printf("%d ", board[pos]);
	if (x == g_size - 1)
		printf("\n");
	if (board[pos]) {
		possible_values[pos] = 1 << board[pos];
		return ;
	}
	possible_values[pos] = bit_mask;
	while (--at_x >= 0)
		// unset_bit(&possible_values[pos], board[at_x + y * g_size]);
		possible_values[pos] &= ~(1 << board[at_x + y * g_size]);
	while (--at_y >= 0)
		possible_values[pos] &= ~(1 << board[x + at_y * g_size]);	
	remove_possible_values(possible_values, x, y, bit_mask);
	return ;
}
