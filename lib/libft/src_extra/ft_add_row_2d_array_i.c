/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_row_2d_array_i.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:06:28 by Jskehan           #+#    #+#             */
/*   Updated: 2024/05/29 14:37:32 by Jskehan          ###   ########.fr       */
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
char	**ft_add_row_2d_array_i(char **out, char *row, int len)
{
	out[len] = ft_strdup(row);
	if (!out[len])
	{
		ft_free_2d_array(&out);
		return (NULL);
	}
	out[len + 1] = NULL;
	return (out);
}

