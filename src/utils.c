/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:50:35 by dkoca             #+#    #+#             */
/*   Updated: 2024/04/07 06:39:44 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aicu.h"

void print_err(int err)
{
	if (err == ERROR)
		ft_putendl_fd("ERROR.\n", STDERR_FILENO);
	else if (err == INPUT_ERROR)
		ft_putendl_fd("WRONG INPUT.\n", STDERR_FILENO);
	else if (err == ENOMEM)
		ft_putendl_fd("NO MEMORY LEFT.\n", STDERR_FILENO);
	else if (err == INVALID_MOVE)
		ft_putendl_fd("INVALID MOVE. TRY AGAIN.\n", STDERR_FILENO);
	else if (err == INCORRECT_BOARD)
		ft_putendl_fd("BOARD COULD NOT BE CREATED.\n", STDERR_FILENO);
}

size_t *ft_realloc(size_t **ptr, int size, int i)
{
	size_t *new_ptr;
	
	new_ptr = NULL;
	if (!(*ptr))
		return (free(new_ptr), ft_calloc(size, sizeof(size_t)));
	new_ptr = ft_calloc(size, sizeof(size_t));
	while (new_ptr && i < size - 1 && (*ptr)[i])
	{
		new_ptr[i] = (*ptr)[i];
		i++;
	}
	new_ptr[i] = '\0';
	free(*ptr);
	*ptr = NULL;
	return(new_ptr);
}