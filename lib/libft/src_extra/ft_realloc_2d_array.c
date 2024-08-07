/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_2d_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:16:05 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/09 16:25:51 by iverniho         ###   ########.fr       */
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
char	**ft_realloc_2d_array(char **array, int new_size)
{
	char	**out;
	int		len;

	len = ft_2d_array_len(array);
	if (new_size <= len)
		return (array);
	out = (char **)ft_calloc(new_size, sizeof(char *));
	if (!out)
		return (NULL);
	out = (ft_splice_2d_array(out, array, 0));
	if (!out)
	{
		ft_free_2d_array(&out);
		return (NULL);
	}
	ft_free_2d_array(&array);
	return (out);
}
