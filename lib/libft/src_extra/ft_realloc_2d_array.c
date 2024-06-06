/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_2d_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:16:05 by Jskehan           #+#    #+#             */
/*   Updated: 2024/06/06 16:53:57 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/**
 * Function: ft_realloc_2d_array
 * -----------------------------
 * Reallocates memory for a 2D array.
 *
 * @param array: A pointer to a 2D array.
 * @param new_size: The new size of the array.
 *
 * @return: The new 2D array with the new size.
 *
 * Note: The array must be NULL-terminated.
 */

char	**ft_realloc_2d_array(char ***array, int new_size)
{
	char	**out;
	int		len;

	len = ft_2d_array_len(*array);
	if (new_size <= len)
		return (*array);
	out = (char **)ft_calloc(new_size, sizeof(char *));
	if (!out)
		return (NULL);
	if (!ft_splice_2d_array(&out, *array, 0))
	{
		ft_free_2d_array(&out);
		return (NULL);
	}
	ft_free_2d_array(array);
	*array = out;
	return (*array);
}
