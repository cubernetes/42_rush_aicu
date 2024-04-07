/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aicu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:35:03 by dkoca             #+#    #+#             */
/*   Updated: 2024/04/07 19:42:25 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AICU_H
# define AICU_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "../libft/libft.h"
#include <fcntl.h>


typedef struct s_heaps
{
	size_t *heap;
	int *strategy;
	size_t heap_n;
}		t_heaps;

/*main.c*/
int main (int ac, char *argv[]);

/*parse.c*/
int parse_and_fill(int ac, char **argv, t_heaps *heap);
int get_fd(int ac, char *argv[]);
int is_valid_input(int fd, t_heaps *heap);
int parse_input(char *line);

/*utils.c*/
void print_err(int err);
size_t *ft_realloc(size_t **ptr, int size, int i);

/*gameplay.c*/
void	start_game(t_heaps *heap);
int play_nim(int current_heap, t_heaps *heap);
int player_turn(t_heaps *heap, int sticks_left);
int	ai_turn(t_heaps *heap, int current_heap, int sticks_left);
int lose_state(int sticks);
int win_state(int sticks);

#endif