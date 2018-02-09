/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functions_unrelated_to_coordinate          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:28:21 by husui             #+#    #+#             */
/*   Updated: 2017/12/15 19:56:30 by husui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	All utility functions that don't involve a coordinate board begin here.
*/

int			ft_sqrt_lower_bound(int value)
{
	int	i;

	i = 0;
	while (i * i <= value)
		i++;
	if (i * i > value)
		return (--i);
	else
		return (i);
}

int			get_tetromino_count(char *filename)
{
	int		fd;
	int		n_read;
	char	buffer[20];
	char	newline_buffer[1];
	int		count;

	fd = open(filename, O_RDONLY);
	count = 0;
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
	close(fd);
	return (count);
}
