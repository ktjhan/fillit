/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifier_smart_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 15:56:43 by husui             #+#    #+#             */
/*   Updated: 2017/12/15 18:48:09 by husui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	The following three functions are related to checking if the shape of the
**	tetromino block is valid. These shapes can be these (or rotations):
**
**		#
**		#				 #		#
**		#		##		 #		#	 	 ##		 #		##
**		#		##		##		##		##		###		 ##
**
**		I-shape (the vertical shape)
**		O-shape	(4 square cube)
**		J-shape (mirror of the L-shape)
**		L-shape (mirror of the J-shape)
**		S-shape (mirror of the Z-shape)
**		T-shape (three squares in one line, and one adjacent to the middle)
**		Z-shape (mirror of the S-shape, zig-zag piece)
**
**	So, without hard-coding every single piece and every single possible
**	rotation, how can we check if each tetromino is valid? Well, one might
**	notice some commonalities between all tetrominoes:
**		- All of them are connected to each other.
**		- All of our tetrominoes have 4 pieces.
**		- In our input block list of tetrominoes, when we scan through from left
**		to right, and from top to bottom, when we find our first #, all
**		subsequent # signs are either "below it," "below it and left," "right,"
**		or "below and right."
**							 	(Diagram)
**			....					____					____	____
**			..##	----------->	__#*	----------->	__.X -->__X_
**			.##.					****					__X_	_X.X
**			....					****					____	__X_
**	Because of the way we parse the input list, the places where the underline
**	characters are at, it is IMPOSSIBLE to find a # sign. However, the places
**	with a * character, is where we expect to find another # sign.
**	So, what does this mean? It means that after finding our first # sign,
**	the only thing we need to do is go down directly below the first #,
**	or go to the right of the #. Then, we can check left, below, right, and
**	above of that second # sign. Then, recurse. Each time we go through a #,
**	we replace the # sign with a "." so that recursive calls don't loop back.
**	This is how we can make it so that at the second # sign, it doesn't recount
**	the first # sign, by replacing the first # sign with a "."
**	Here is the workflow:
**	1) bad_shape() (third function down) creates the Cartesian 2D grid we need.
**	bad_shape() first calls bad_shape_first_coordinates(), storing its results,
**	then it calls bad_shape_seeker() and compares the result to 4.
**
**	2) bad_shape_first_coordinates() (second function down) finds the
**	upper-leftmost and fills that information into first_coordinates[2]
**	created during bad_shape.
**
**	3) bad_shape_seeker() is the one doing the recursive logic explained above.
**	It starts off at a (y, x) (where the first # sign is), and then goes down
**	and right simultaneously with recursive calls.
*/

static void	bad_shape_first_coordinates(char *tetromino_block, int *array)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (*tetromino_block)
	{
		if (*tetromino_block == '\n')
		{
			x = 0;
			y++;
			tetromino_block++;
			if (*tetromino_block == '\0')
				break ;
		}
		if (*tetromino_block == '#')
		{
			array[0] = x;
			array[1] = y;
			return ;
		}
		x++;
		tetromino_block++;
	}
}

static int	bad_shape_seeker(char tetromino_block[4][4], int x, int y)
{
	int		piece_count;

	if (x < 0 || x > 3)
		return (0);
	if (y < 0 || y > 3)
		return (0);
	if (tetromino_block[x][y] == '.')
		return (0);
	if (tetromino_block[x][y] == '#')
	{
		tetromino_block[x][y] = '.';
		piece_count = 1
			+ bad_shape_seeker(tetromino_block, x, y - 1)
			+ bad_shape_seeker(tetromino_block, x - 1, y)
			+ bad_shape_seeker(tetromino_block, x + 1, y)
			+ bad_shape_seeker(tetromino_block, x, y + 1);
		return (piece_count);
	}
	return (0);
}

static int	bad_shape(char *tetromino_block)
{
	char	array[4][4];
	int		first_position[2];
	int		x;
	int		y;

	x = 0;
	y = 0;
	bad_shape_first_coordinates(tetromino_block, first_position);
	while (*tetromino_block)
	{
		if (*tetromino_block == '\n')
		{
			x = 0;
			y++;
			tetromino_block++;
			if (*tetromino_block == '\0')
				break ;
		}
		array[x][y] = *tetromino_block;
		x++;
		tetromino_block++;
	}
	if (bad_shape_seeker(array, first_position[0], first_position[1]) != 4)
		return (1);
	return (0);
}

/*
**	The function bad_tetromino accepts string representations of the board as
**	input.
*/

static int	bad_tetromino(char *tetromino_block)
{
	if (!bad_block_size(tetromino_block))
		if (!bad_characters(tetromino_block))
			if (!bad_number_of_characters(tetromino_block))
				if (!bad_shape(tetromino_block))
					return (0);
	return (1);
}

int			verify_if_bad_tetromino_list(char *filename)
{
	int		fd;
	int		bytes_read_for_newline;
	int		bytes_read_for_tetromino;
	char	buffer[21];
	char	newline_buffer[1];

	buffer[20] = '\0';
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	bytes_read_for_tetromino = read(fd, buffer, 20);
	if (bytes_read_for_tetromino == 0)
		return (1);
	while (bytes_read_for_tetromino > 0)
	{
		if (bad_tetromino(buffer))
			return (1);
		bytes_read_for_newline = read(fd, newline_buffer, 1);
		bytes_read_for_tetromino = read(fd, buffer, 20);
		if (bytes_read_for_newline > 0 && bytes_read_for_tetromino != 20)
			return (1);
	}
	close(fd);
	return (0);
}
