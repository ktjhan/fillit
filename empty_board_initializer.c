/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_board_initializer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 15:54:24 by husui             #+#    #+#             */
/*   Updated: 2017/12/15 18:49:07 by husui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	The following three functions relate to creating a new, empty board
**	of size "size_of_square," shown in the third function down,
**	initialize_square(). It takes in an integer, then produces a
**	string representation of an empty board. Take note that the
**	actual size of the board is size_of_square + 1, because all
**	boards start off at a single ".". Calling initialize_square(3),
**	for example, creates a board of size 4. Calling initialize_square(0)
**	returns a board that is of size 1, a single ".".
*/

static char	*insert_character(char *array, char c, int index)
{
	char	*new;
	int		i;

	new = (char *)malloc(sizeof(char) * (ft_strlen(array) + 2));
	new[ft_strlen(array) + 1] = '\0';
	i = 0;
	while (index--)
		new[i++] = *array++;
	new[i++] = c;
	while (*array)
		new[i++] = *array++;
	return (new);
}

char		*expand_square(char *array)
{
	char	*new;
	char	*new2;
	int		i;
	int		j;

	new = ft_strdup(array);
	i = 0;
	while (new[i])
	{
		while (new[i] != '\n')
			i++;
		new = insert_character(new, '.', i);
		i += 2;
	}
	j = 0;
	while (new[j] != '\n')
		j++;
	j++;
	new2 = (char *)malloc(sizeof(char) * i + j + 2);
	ft_strcpy(new2, new);
	new2[i + j--] = '\0';
	new2[i + j--] = '\n';
	while (j >= 0)
		new2[i + j--] = '.';
	return (new2);
}

char		*initialize_square(int size_of_square)
{
	char	*new;
	char	*square;

	new = ".\n";
	if (size_of_square == 0)
		return (new);
	square = expand_square(new);
	size_of_square--;
	while (size_of_square--)
		square = expand_square(square);
	return (square);
}
