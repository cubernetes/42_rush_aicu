/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 04:20:47 by dkoca             #+#    #+#             */
/*   Updated: 2024/04/07 20:43:34 by dkoca            ###   ########.fr       */
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
		ft_putstr_fd(str, STDOUT_FILENO);
}

void print_board(t_heaps *heap)
{
	size_t i;

	i = (size_t)-1;
	while (++i < heap->heap_n)
	{
		ft_printf("%d: ", (int)heap->heap[i]);
		repeat_string("| ", heap->heap[i]);
		ft_putendl_fd("", STDOUT_FILENO);
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
	// if (current_heap > 0 && (heap->heap[current_heap - 1] % 4) == 1)
	// {
	// 	if ((heap->heap[current_heap] % 4) == 1)
	// 		take = 1;
	// 	else if ((heap->heap[current_heap] % 4) == 0) /* above heap is 4k+1 and cur heap is 4k, but we want p2 to start on the next heap so we should NOT take 3. Take either 2 or 1, in which one are the chances of ai higher????*/
	// 		take = 1; // or 2
	// 	else if ((heap->heap[current_heap] % 4) == 2)
	// 		take = 2; // leave them with 4, take the rest
	// 	else if ((heap->heap[current_heap] % 4) == 3)
	// 		take = 3;
	// }
	// else
	// 	take = win_state(sticks_left);
	return (take);
}

int player_turn(t_heaps *heap, int sticks_left)
{
	char *line;
	int taken = 0;
	int value;
	static int fd = -2;
	
	print_board(heap);
	fd = open("/dev/tty", O_RDONLY);
	line = get_next_line(fd);
	value = ft_atoi(line);
	while (line && (value < 1 || value > 3 || value > sticks_left)) // wrong input
	{
		free(line);
		ft_putendl_fd("Try again. Between 1-3:", STDOUT_FILENO);
		line = get_next_line(fd);
		value = ft_atoi(line);
	}
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
	
	while (--current_heap >= 0)
	{
		sticks_left = heap->heap[current_heap];
		// printf("cur heap = %i\n", current_heap);
		// printf(" = %i\n", current_heap);
		printf("Sticks at the start of the heap = %i\n", sticks_left);
		while (sticks_left > 0)
		{
			/* ai's turn */
			ft_putendl_fd("AI's move:", STDOUT_FILENO);
			taken_sticks = ai_turn(heap, current_heap, sticks_left);
			ft_printf("AI took %d sticks\n", taken_sticks);
			//update array
			sticks_left -= taken_sticks;
			// printf("Sticks left = %i\n", sticks_left);
			heap->heap[current_heap] = sticks_left; 
			//check if sticks left are 0 and if there are still heaps
			// if true, move on to the upper heap and update total sticks
			if (sticks_left == 0 && current_heap > 0)
			{
				current_heap--;
				sticks_left = heap->heap[current_heap];
				// printf("Sticks left (next heap) = %i\n", sticks_left);
			}
			//if sticks == 0 AND heaps == 0, player wins instead of AI
			if (sticks_left == 0 && current_heap == 0)
				return (PLAYER_WINS);
			/* player's turn */
			ft_putendl_fd("Your move. Between 1-3:",STDOUT_FILENO);
			taken_sticks = ai_turn(heap, current_heap, sticks_left);
			// taken_sticks = player_turn(heap, sticks_left);
			ft_printf("You took %d sticks\n", taken_sticks);
			//update array
			sticks_left -= taken_sticks;
			// printf("Sticks left = %i\n", sticks_left);
			heap->heap[current_heap] = sticks_left;
			//if sticks == 0 AND heaps == 0, AI wins
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
		ft_putendl_fd("Player wins!", STDOUT_FILENO);
	else
		ft_putendl_fd("AI wins!", STDOUT_FILENO);
}