/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 14:21:55 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/03 18:02:03 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH01_H
# define RUSH01_H
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

//TO REMOVE
# include <stdio.h>
//END OF REMOVE

//DEFINES
# define VIEWS_MIN 4
# define NO_SOLUTIONS 1
# define BAD_SOLUTION 1
# define IS_SOLVED 1
# define IS_NOT_SOLVED 0

uid_t	g_size;

//INITIALIZATION
uid_t	get_map_size(int argc, char *const *argv);

//CHECKER

//SOLVING
int		solver(uid_t *board, uid_t x, uid_t y);

//UTILS
int		ft_sqrt(int nb);
bool	is_digit(char c);
void	print_views(uid_t *views);
bool	print_board(uid_t *board);

#endif