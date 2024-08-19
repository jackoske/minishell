/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_row_2d_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:06:28 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/19 15:22:13 by Jskehan          ###   ########.fr       */
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
 * @param free_row: A flag indicating whether to free the row after adding.
 *
 * @return: The new 2D array with the added row.
 *
 * Note: The array must be NULL-terminated.
 */
static char	**allocate_new_array(int size)
{
	char	**new_array;

	new_array = ft_calloc(size + 1, sizeof(char *));
	if (!new_array)
		return (NULL);
	return (new_array);
}

static int	copy_existing_rows(char **new_array, char **array, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		new_array[i] = ft_strdup(array[i]);
		if (!new_array[i])
		{
			ft_free_2d_array(&new_array);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	add_new_row(char **new_array, char *row, int index, int free_row)
{
	new_array[index] = ft_strdup(row);
	if (!new_array[index])
	{
		ft_free_2d_array(&new_array);
		return (0);
	}
	if (free_row)
		free(row);
	return (1);
}

char	**ft_add_row_2d_array(char **array, char *row, int free_row)
{
	int		i;
	char	**new_array;

	i = 0;
	if (!row)
		return (array);
	if (!array)
	{
		new_array = allocate_new_array(1);
		if (!new_array || !add_new_row(new_array, row, 0, free_row))
			return (NULL);
		return (new_array);
	}
	while (array[i])
		i++;
	new_array = allocate_new_array(i + 1);
	if (!new_array || !copy_existing_rows(new_array, array, i)
		|| !add_new_row(new_array, row, i, free_row))
		return (NULL);
	ft_free_2d_array(&array);
	return (new_array);
}
