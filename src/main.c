/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:26:46 by dkoca             #+#    #+#             */
/*   Updated: 2024/04/07 21:04:31 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aicu.h"

int init_heaps(t_heaps *heap)
{
	heap->heap = NULL;
	heap->strategy = NULL;
	heap->heap_n = 0;
	return (EXIT_SUCCESS);
}
int main (int ac, char *argv[])
{
	// int fd;
	t_heaps *heap;
	
	heap = ft_calloc(1, sizeof(t_heaps));
	if (!heap)
		return (print_err(ENOMEM), ERROR);
	init_heaps(heap);
	if (parse_and_fill(ac, argv, heap) == -1)
		return (free(heap->heap), free(heap), ERROR);
	//start the game
	start_game(heap);
	free(heap->heap);
	free(heap->strategy);
	free(heap);
	return (EXIT_SUCCESS);	
}