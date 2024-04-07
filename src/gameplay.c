/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 04:20:47 by dkoca             #+#    #+#             */
/*   Updated: 2024/04/07 23:40:19 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aicu.h"

int win_state(int sticks)
{
	int take = 0;
	
	if (sticks % 4 == 0)
		take = 3;
	else if (sticks % 4 == 1) // lose state, but for the other player
		take = 1;
	else if (sticks % 4 == 2)
		take = 1;
	else if (sticks % 4 == 3)
		take = 2;
	return (take);
}

int lose_state(int sticks)
{
	int take = 0;
	
	if (sticks % 4 == 0)
		take = 1; // or 2, leaving us the chance to win
	else if (sticks % 4 == 1)
		take = 1;
	else if (sticks % 4 == 2)
		take = 2;
	else if (sticks % 4 == 3)
		take = 3;
	return (take);
}

void repeat_string(char *str, size_t n)
{
	while (n--)
		ft_printf("%s", str);
}

void	my_sleep(void)
{
	long	i;

	i = 0;
	while (i < 20000000)
		i += 1;
}

void print_board(t_heaps *heap)
{
	size_t i;

	ft_printf("The board:\n");
	i = (size_t)-1;
	while (++i < heap->heap_n)
	{
		if (heap->heap[i] == 0)
			continue;
		ft_printf("%d: ", (int)heap->heap[i]);
		repeat_string(" |", heap->heap[i]);
		ft_printf("\n");
	}
}

int	ai_turn(t_heaps *heap, int current_heap, int sticks_left)
{
	int take = 0;
	
	print_board(heap);
	if (heap->strategy[current_heap] == WIN)
		take = win_state(sticks_left);	
	else
		take = lose_state(sticks_left);	
	return (take);
}

int player_turn(t_heaps *heap, int sticks_left)
{
	char *line;
	int taken = 0;
	int value;
	static int fd = -2;
	
	print_board(heap);
	ft_printf("Your move (1 to 3): ");
	fd = open("/dev/tty", O_RDONLY);
	line = get_next_line(fd);
	value = ft_atoi(line);
	while (line && (value < 1 || value > 3 || value > sticks_left)) // wrong input
	{
		free(line);
		ft_printf("\033[A\rTry again (must be between 1 and 3): ");
		ft_printf("          " "\b\b\b\b\b\b\b\b\b\b");
		line = get_next_line(fd);
		value = ft_atoi(line);
	}
	close(fd);
	get_next_line(fd);
	if (line)
	{
		taken = value;
		free(line);
	}
	return (taken);
}

int play_nim(int current_heap, t_heaps *heap)
{
	int sticks_left;
	size_t taken_sticks;
	
	ft_printf("\033[H\033[2J\033[3J");
	while (--current_heap >= 0)
	{
		sticks_left = heap->heap[current_heap];
		while (sticks_left > 0)
		{
			/* ai's turn */
			taken_sticks = ai_turn(heap, current_heap, sticks_left);
			ft_printf("AI took %d stick%s\n\n", taken_sticks, taken_sticks == 1 ? "" : "s");
			my_sleep();
			// ft_printf("\033[H\033[2J\033[3J");
			ft_printf("\033[H\033[2J");
			// update array
			sticks_left -= taken_sticks;
			heap->heap[current_heap] = sticks_left; 
			// check if sticks left are 0 and if there are still heaps
			// if true, move on to the upper heap and update total sticks
			if (sticks_left == 0 && current_heap > 0)
			{
				current_heap--;
				sticks_left = heap->heap[current_heap];
			}
			// if sticks == 0 AND heaps == 0, player wins instead of AI
			if (sticks_left == 0 && current_heap == 0)
				return (PLAYER_WINS);
			/* player's turn */
			// taken_sticks = ai_turn(heap, current_heap, sticks_left);
			taken_sticks = player_turn(heap, sticks_left);
			ft_printf("You took %d stick%s\n\n", taken_sticks, taken_sticks == 1 ? "" : "s");
			my_sleep();
			// ft_printf("\033[H\033[2J\033[3J");
			ft_printf("\033[H\033[2J");
			//update array
			sticks_left -= taken_sticks;
			heap->heap[current_heap] = sticks_left;
			if (sticks_left == 0 && current_heap == 0)
				return(AI_WINS);
		}
	}
	//otherwise player wins
	return (PLAYER_WINS);			
}

void	start_game(t_heaps *heap)
{
	int current_heap;
	
	current_heap = heap->heap_n;
	if (play_nim(current_heap, heap) == PLAYER_WINS)
		ft_printf("You win!!!\n");
	else
		ft_printf("AI wins!!!\n");
}
