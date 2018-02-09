/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storing_tetrominoes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 15:48:29 by husui             #+#    #+#             */
/*   Updated: 2017/12/15 19:08:45 by husui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	End of functions that create a new, empty board of size "size_of_square".
*/

/*
**	Beginning for functions related to parsing the input list of tetrominoes,
**	creating an array of triple pointers to an integer. The data structure
**	for each tetromino goes three tiers deep. Let us exemplify 9 teetrominoes:
**	1) First pointer keeps track of all 9 tetrominoes.
**		[0, 1, 2, 3, 4, 5, 6, 7, 8]
**	2) Second pointer keeps track of all 4 # signs found in a tetromino.
**		[First #, Second #, Third #, Fourth #]
**	3) Third pointer keeps track of Cartesian coordinates (y, x), and letter.
**		[y, x, 'A']
**	Altogether, here is what a tetromino input list looks like:
**		[ [[y, x, 'A'], [y, x, 'A'], [y, x, 'A'], [y, x, 'A']],
**		  [[y, x, 'B'], [y, x, 'B'], [y, x, 'B'], [y, x, 'B']],
**	 	  . . .
**	 	  . . .
**	 	  . . .
**		  [[y, x, 'I'], [y, x, 'I'], [y, x, 'I'], [y, x, 'I']] ]
**	It's fine to store the letter information as an integer, since chars
**	convert easily. However, in retrospect, it wasn't absolutely necessary to.
**	store the letter in every single tetromino piece.
**	I just did it for the safety of knowing if I had to reorder the tetromino
**	list, the letter information would propagate through the reorder.
*/

int			***g_t_a_p_f_t_p(char *filename, int count, int fd, int n_read)
{
	char	buffer[20];
	char	newline_buffer[1];

	fd = open(filename, O_RDONLY);
	n_read = read(fd, buffer, 20);
	if (n_read > 0)
		count++;
	read(fd, newline_buffer, 1);
	n_read = read(fd, buffer, 20);
	while (n_read > 0)
	{
		n_read = read(fd, buffer, 20);
		read(fd, newline_buffer, 1);
		count++;
	}
	g_tetromino_array = (int ***)malloc(sizeof(int *) * count + 1);
	g_tetromino_array[count] = (int **)1234567890;
	close(fd);
	return (g_tetromino_array);
}

static int	**t_c_pairs(char *tetromino, int x, int y, int i)
{
	int		**new;
	int		*pair;
	int		**new_iter;

	new = (int **)malloc(sizeof(int *) * 4);
	new_iter = new;
	while (*tetromino)
	{
		if (*tetromino == '#')
		{
			pair = (int *)malloc(sizeof(int *) * 3);
			pair[0] = y;
			pair[1] = x;
			pair[2] = i + 'A';
			*new_iter++ = pair;
		}
		if (*tetromino++ == '\n')
		{
			x = 0;
			y++;
		}
		else
			x++;
	}
	return (new);
}

void		fill_tetromino_array(char *filename)
{
	int		fd;
	int		n_read;
	char	buffer[21];
	char	newline_buffer[1];
	int		i;

	buffer[20] = '\0';
	i = 0;
	fd = open(filename, O_RDONLY);
	n_read = read(fd, buffer, 20);
	g_tetromino_array[i] = t_c_pairs(buffer, 0, 0, 0);
	if (n_read > 0)
		i++;
	read(fd, newline_buffer, 1);
	while (n_read > 0)
	{
		n_read = read(fd, buffer, 20);
		g_tetromino_array[i] = t_c_pairs(buffer, 0, 0, i);
		n_read = read(fd, newline_buffer, 1);
		if (n_read < 0)
			break ;
		i++;
	}
	close(fd);
}

/*
**	End of functions that create a triple array of integers.
*/
