/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinate_board_utility_functions_smart.          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 15:40:14 by husui             #+#    #+#             */
/*   Updated: 2017/12/15 19:50:16 by husui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	insert_piece(char **c_b, int **t_c_pairs, int y, int x)
{
	int	y_relative;
	int	x_relative;
	int	i;
	int	size;

	if (y < 0 || x < 0)
		return ;
	size = board_size(c_b);
	i = 0;
	c_b[y][x] = t_c_pairs[0][2];
	while (i < 3)
	{
		y_relative = t_c_pairs[i + 1][0] - t_c_pairs[i][0];
		x_relative = t_c_pairs[i + 1][1] - t_c_pairs[i][1];
		y = y + y_relative;
		x = x + x_relative;
		if (y >= 0 && y < size && x >= 0 && x < size)
			c_b[y][x] = t_c_pairs[0][2];
		i++;
	}
	return ;
}

void		delete(char **c_b, int **t_c_pairs, int y, int x)
{
	int		y_relative;
	int		x_relative;
	int		i;
	int		size;

	if (y < 0 || x < 0)
		return ;
	size = board_size(c_b);
	i = 0;
	c_b[y][x] = '.';
	while (i < 3)
	{
		y_relative = t_c_pairs[i + 1][0] - t_c_pairs[i][0];
		x_relative = t_c_pairs[i + 1][1] - t_c_pairs[i][1];
		y = y + y_relative;
		x = x + x_relative;
		if (y >= 0 && y < size && x >= 0 && x < size)
			c_b[y][x] = '.';
		i++;
	}
	return ;
}

static int	fit(char **c_b, int **t_c_pairs, int y, int x)
{
	int		letters;
	char	**future;
	char	*board;

	board = b_s(c_b, 0, 0, 0);
	letters = get_number_of_letters_on_board(c_b);
	future = b_c(board);
	insert_piece(future, t_c_pairs, y, x);
	if ((get_number_of_letters_on_board(future) - letters) == 4)
		return (1);
	return (0);
}

int			insert(char **c_b, int **t_c_pairs, int y, int x)
{
	if (fit(c_b, t_c_pairs, y, x))
	{
		insert_piece(c_b, t_c_pairs, y, x);
		return (1);
	}
	else
		return (0);
}
