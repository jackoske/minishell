/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_row_2d_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:06:28 by Jskehan           #+#    #+#             */
/*   Updated: 2024/05/29 18:06:30 by Jskehan          ###   ########.fr       */
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
	int		len;
	char	**out;

	if (!row)
		return (array);
	len = ft_2d_array_len(array);
	out = ft_realloc_2d_array(array, len + 1);
	if (!out)
		return (NULL);
	out = ft_add_row_2d_array_i(out, row, len);
	return (out);
}
