/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_solved.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:55:26 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/02 13:17:32 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

// pruid_tf("top view count for x = %d = %d\n", curr_x, view_count);
static uid_t	top_views(t_pos *board, uid_t size, uid_t curr_x)
{
	uid_t	view_count;
	uid_t	highest;
	uid_t	current_height;
	uid_t	i;

	i = 0;
	view_count = 0;
	highest = 0;
	while (i < size)
	{
		current_height = board[curr_x + (i * size)].value;
		if (current_height > highest)
		{
			view_count++;
			highest = current_height;
		}
		i++;
	}
	return (view_count);
}

// pruid_tf("bottom view count for x = %d = %d\n", curr_x, view_count);
static uid_t	bottom_views(t_pos *board, uid_t size, uid_t curr_x)
{
	uid_t	view_count;
	uid_t	highest;
	uid_t	current_height;
	uid_t	i;

	i = size;
	view_count = 0;
	highest = 0;
	while (i > 0)
	{
		current_height = board[curr_x + ((i - 1) * size)].value;
		if (current_height > highest)
		{
			view_count++;
			highest = current_height;
		}
		i--;
	}
	return (view_count);
}

// pruid_tf("left view count for y = %d = %d\n", curr_y, view_count);
static uid_t	left_views(t_pos *board, uid_t size, uid_t curr_y)
{
	uid_t	view_count;
	uid_t	highest;
	uid_t	current_height;
	uid_t	i;

	i = 0;
	view_count = 0;
	highest = 0;
	while (i < size)
	{
		current_height = board[size * curr_y + i].value;
		if (current_height > highest)
		{
			view_count++;
			highest = current_height;
		}
		i++;
	}
	return (view_count);
}

// pruid_tf("right view count for y = %d = %d\n", curr_y, view_count);
static uid_t	right_views(t_pos *board, uid_t size, uid_t curr_y)
{
	uid_t	view_count;
	uid_t	highest;
	uid_t	current_height;
	uid_t	i;

	i = size;
	view_count = 0;
	highest = 0;
	while (i > 0)
	{
		current_height = board[i - 1 + (size * curr_y)].value;
		if (current_height > highest)
		{
			view_count++;
			highest = current_height;
		}
		i--;
	}
	return (view_count);
}

bool	is_solved(t_pos	*board, uid_t *views, uid_t	size)
{
	uid_t			i;

	// printf("\n\n--- ENTERED IS_SOLVED() ---\n\n");
	// print_board(board, size);

	i = 0;
	if (there_are_duplicates(board, size))
		return (IS_NOT_SOLVED);
	while (i < size)
	{
		if (top_views(board, size, i) != views[i + (0 * size)]  || \
			bottom_views(board, size, i) != views[i + (1 * size)]  || \
			left_views(board, size, i) != views[i + (2 * size)]  || \
			right_views(board, size, i) != views[i + (3 * size)] )
			return (IS_NOT_SOLVED);
		// printf("top_views: %d\n", top_views(board, size, i));
		// printf("views[i + (0 * size): %d\n", views[i + (0 * size)]);
		// printf("bottom_views: %d\n", bottom_views(board, size, i));
		// printf("views[i + (1 * size): %d\n", views[i + (1 * size)]);
		// printf("left_views: %d\n", left_views(board, size, i));
		// printf("views[i + (2 * size): %d\n", views[i + (2 * size)]);
		// printf("right_views: %d\n", right_views(board, size, i));
		// printf("views[i + (3 * size): %d\n", views[i + (3 * size)]);
		i++;
	}
	return (IS_SOLVED);
}
