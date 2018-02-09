/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifier_dumb_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 16:02:23 by husui             #+#    #+#             */
/*   Updated: 2017/12/15 19:55:57 by husui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		bad_block_size(char *tetromino_block)
{
	int	characters_in_one_line;

	characters_in_one_line = 0;
	if (tetromino_block[4] != '\n' || tetromino_block[9] != '\n' ||
			tetromino_block[14] != '\n' || tetromino_block[19] != '\n')
		return (1);
	while (*tetromino_block)
	{
		if (*tetromino_block == '\n')
		{
			if (characters_in_one_line != 4)
				return (1);
			characters_in_one_line = 0;
			tetromino_block++;
		}
		if (*tetromino_block == '\0')
			break ;
		characters_in_one_line++;
		if (characters_in_one_line > 4)
			return (1);
		tetromino_block++;
	}
	return (0);
}

int		bad_characters(char *tetromino_block)
{
	while (*tetromino_block)
	{
		if (!(*tetromino_block == '.' || *tetromino_block == '#' ||
					*tetromino_block == '\n'))
			return (1);
		tetromino_block++;
	}
	return (0);
}

int		bad_number_of_characters(char *tetromino_block)
{
	int	count;

	count = 0;
	while (*tetromino_block)
	{
		count++;
		tetromino_block++;
	}
	if (count != 20)
		return (1);
	return (0);
}
