/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:45:32 by Jskehan           #+#    #+#             */
/*   Updated: 2024/07/22 16:37:42 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/**
 * Function: ft_free_2d_array
 * --------------------------
 * Frees a 2D array and sets the pointer to NULL.
 *
 * @param array: A pointer to a 2D array.
 * This function iterates over the first dimension of the array
	and frees each sub-array.
 * After all sub-arrays have been freed, it frees the array itself.
 * it sets the pointer to the array to NULL to prevent dangling pointer issues.
 *
 * Note: This function assumes that the array ends with a NULL pointer.
 */
void	ft_free_2d_array(char ***array)
{
	int	i;

	if (!array || !*array)
		return ;
	i = 0;
	while ((*array)[i])
	{
		free((*array)[i]);
		(*array)[i] = NULL;
		i++;
	}
	free(*array);
	*array = NULL;
}
