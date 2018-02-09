/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 15:28:29 by husui             #+#    #+#             */
/*   Updated: 2017/12/15 19:49:06 by husui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	Here is the recursive function meant to find the first possible arrangement
**	of all tetrominos. It is coded in such a way that we have a guarantee
**	that the first arrangement of all tetrominoes on a board is, in fact, the
**	smallest square. Once that is found, the entire function terminates early
**	without having to continue forward. This avoids going through every
**	permutation and taking forever.
*/

int	solve(char *board, char **c_b, int t_c)
{
	int		y;
	int		x;

	if (t_c == g_tetromino_count)
	{
		g_smallest = board;
		return (0);
	}
	y = 0;
	while (c_b[y])
	{
		x = 0;
		while (c_b[y][x])
		{
			if (insert(c_b, g_tetromino_array[t_c], y, x))
			{
				if (!solve(b_s(c_b, 0, 0, 0), b_c(b_s(c_b, 0, 0, 0)), t_c + 1))
					return (0);
				delete(c_b, g_tetromino_array[t_c], y, x);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	char	*board;
	int		lower_bound;
	int		size;

	if (argc != 2)
	{
		ft_putstr("usage: fillit source_file\n");
		exit(0);
	}
	if (verify_if_bad_tetromino_list(argv[1]))
	{
		ft_putstr("error\n");
		exit(1);
	}
	g_tetromino_count = get_tetromino_count(argv[1]);
	lower_bound = ft_sqrt_lower_bound(g_tetromino_count);
	board = initialize_square(lower_bound);
	size = board_size(b_c(board));
	g_smallest = 0;
	g_tetromino_array = g_t_a_p_f_t_p(argv[1], 0, 0, 0);
	fill_tetromino_array(argv[1]);
	while (solve(board, b_c(board), 0))
		board = initialize_square(size++);
	ft_putstr(g_smallest);
}
