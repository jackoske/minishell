/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_row_2d_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:06:28 by Jskehan           #+#    #+#             */
/*   Updated: 2024/06/07 16:49:39 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Function: ft_add_row_2d_array
 * -----------------------------
 * Adds a row to a 2D array.
 *
 * @param array: A pointer to a 2D array.
 * @param row: The row to add.
 *
 * @return: The new 2D array with the added row.
 *
 * Note: The array must be NULL-terminated.
 */
char	**ft_add_row_2d_array(char **array, char *row)
{
	int		i;
	char	**new_array;

	i = 0;
	if (!row)
		return (array);
	if (!array)
	{
		new_array = ft_calloc(2, sizeof(char *));
		if (!new_array)
			return (NULL);
		new_array[0] = ft_strdup(row);
		new_array[1] = NULL;
		return (new_array);
	}
	while (array[i])
		i++;
	new_array = ft_calloc(i + 2, sizeof(char *));
	if (!new_array)
		return (NULL);
	i = -1;
	while (array[++i])
		new_array[i] = ft_strdup(array[i]);
	new_array[i] = ft_strdup(row);
	new_array[i + 1] = NULL;
	ft_free_2d_array(&array);
	return (new_array);
}
