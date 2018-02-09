/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board_converters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 15:44:36 by husui             #+#    #+#             */
/*   Updated: 2017/12/15 19:49:54 by husui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	Beginning of functions related to converting a string representation
**	of our tetris square into coordinate form. By coordinate form, I mean
**	that it is a double array where the first pointer tracks the y-
**	axis, and the second pointer tracks the x-axis. It is a little bit
**	odd to have the y-axis go first, I agree, but the reason I
**	implemented the first pointer to be on the y-axis is because in terms
**	of a string, each line is responsible for a set of characters, and
**	it's easier to think of each character as being an "x".
**
**	b_c() is called in the main(), and it initializes
**	the first array based on the number of lines. Then, it
**	called fill_coordinate_board() to insert all of the x-values, moving
**	the y-axis forward whenever it reaches a newline character.
**
**	b_s() takes a coordinate_board() object, and converts it back
**	into a string. In this way, we can be very flexible between both types
**	and yet still do operations that involve can only coordinate boards or
**	string representations.
*/

static void	fill_coordinate_board(char *board, char **new_board, int nb_lines)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (*board)
	{
		if (x == 0)
			new_board[y] = (char *)malloc(sizeof(char) * (nb_lines + 1));
		if (*board == '\n')
		{
			new_board[y][x] = '\0';
			x = 0;
			y++;
			board++;
		}
		else
		{
			new_board[y][x] = *board;
			x++;
			board++;
		}
		if (!*board)
			break ;
	}
}

char		**b_c(char *board)
{
	char	**new;
	char	*iter;
	int		y;

	y = 0;
	iter = board;
	while (*iter)
	{
		if (*iter == '\n')
			y++;
		iter++;
	}
	new = (char **)malloc(sizeof(char *) * (y + 1));
	new[y] = 0;
	fill_coordinate_board(board, new, y);
	return (new);
}

char		*b_s(char **board, int count, int y, int x)
{
	char	*new;

	while (board[y])
	{
		x = 0;
		while (board[y][x++])
			count++;
		count++;
		y++;
	}
	new = (char *)malloc(sizeof(char) * (count + 1));
	new[count] = '\0';
	count = 0;
	y = 0;
	while (board[y])
	{
		x = 0;
		while (board[y][x])
			new[count++] = board[y][x++];
		new[count++] = '\n';
		y++;
	}
	return (new);
}
