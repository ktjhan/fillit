/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinate_board_utility_functions_dumb.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 15:42:06 by husui             #+#    #+#             */
/*   Updated: 2017/12/15 18:53:06 by husui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		print_coordinate_board(char **coordinate_board)
{
	int		x;
	int		y;

	y = 0;
	x = 0;
	while (coordinate_board[y])
	{
		x = 0;
		while (coordinate_board[y][x])
		{
			ft_putchar(coordinate_board[y][x]);
			x++;
		}
		if (coordinate_board[y][x] == '\0')
			ft_putstr("\n");
		y++;
	}
}

int			get_number_of_letters_on_board(char **coordinate_board)
{
	int		count;
	int		y;
	int		x;
	char	letter;

	count = 0;
	y = 0;
	while (coordinate_board[y])
	{
		x = 0;
		while (coordinate_board[y][x])
		{
			letter = coordinate_board[y][x];
			if ('A' <= letter && letter <= 'Z')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

int			board_size(char **coordinate_board)
{
	int		y;
	int		count;

	if (!coordinate_board)
		return (2147483647);
	count = 0;
	y = 0;
	while (coordinate_board[y])
	{
		y++;
		count++;
	}
	return (count);
}
