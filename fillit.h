/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:29:13 by husui             #+#    #+#             */
/*   Updated: 2017/12/15 19:51:24 by husui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H

# define FILLIT_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_strcpy(char *dst, const char *src);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *c);
void	ft_putstr(char *str);
void	ft_putchar(char c);
char	**b_c(char *board);
char	*b_s(char **board, int count, int y, int x);
void	print_coordinate_board(char **coordinate_board);
int		board_size(char **cordinate_board);
void	delete(char **c_b, int **t_c_pairs, int y, int x);
int		insert(char **c_b, int **t_c_pairs, int y, int x);
char	*expand_square(char *array);
char	*initialize_square(int size_of_square);
int		***g_t_a_p_f_t_p(char *filename, int count, int fd, int n_read);
int		ft_sqrt_lower_bound(int value);
int		get_tetromino_count(char *filename);
int		bad_block_size(char *tetromino_block);
int		bad_characters(char *tetromino_block);
int		bad_number_of_characters(char *tetromino_block);
int		verify_if_bad_tetromino_list(char *filename);
int		get_number_of_letters_on_board(char **coordinate_board);
void	fill_tetromino_array(char *filename);

int		***g_tetromino_array;
int		g_tetromino_count;
char	*g_smallest;
#endif
