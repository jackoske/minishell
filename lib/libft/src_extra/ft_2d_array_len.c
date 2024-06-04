/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2d_array_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:27:47 by Jskehan           #+#    #+#             */
/*   Updated: 2024/05/28 15:32:59 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/**
 * Function: ft_2d_array_len
 * -------------------------
 * Returns the length of a 2D array.
 *
 * @param array: A pointer to a 2D array.
 *
 * @return: The length of the 2D array.
 *
 * Note: This function assumes that the array ends with a NULL pointer.
 */
int	ft_2d_array_len(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		i++;
	return (i);
}
