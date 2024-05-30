/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_2d_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:16:05 by Jskehan           #+#    #+#             */
/*   Updated: 2024/05/29 14:30:50 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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

char	**copy_old_array(char **out, char **array, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		out[i] = ft_strdup(array[i]);
		if (!out[i])
		{
			ft_free_2d_array(&out);
			return (NULL);
		}
	}
	return (out);
}

char	**ft_realloc_2d_array(char **array, int new_size)
{
	int		len;
	char	**out;

	len = ft_2d_array_len(array);
	if (new_size < len)
		return (array);
	out = ft_new_2d_array(new_size + 1);
	if (!out)
	{
		ft_free_2d_array(&array);
		return (NULL);
	}
	out = copy_old_array(out, array, len);
	if (!out)
		return (NULL);
	ft_free_2d_array(&array);
	return (out);
}
