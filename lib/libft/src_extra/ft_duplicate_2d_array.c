/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_duplicate_2d_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:18:40 by Jskehan           #+#    #+#             */
/*   Updated: 2024/05/29 01:01:19 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Function: ft_duplicate_2d_array
 * -------------------------------
 * Duplicates a 2D array.
 *
 * @param array: A pointer to a 2D array.
 *
 * @return: A pointer to a new 2D array that is a duplicate of the input array.
 *
 * Note: This function assumes that the array ends with a NULL pointer.
 */
char	**ft_duplicate_2d_array(char **array)
{
	char	**dup;
	int		i;

	i = 0;
	dup = (char **)malloc(sizeof(char *) * (ft_2d_array_len(array) + 1));
	if (!dup)
		return (NULL);
	while (array && array[i])
	{
		dup[i] = ft_strdup(array[i]);
		if (!dup[i])
		{
			ft_free_2d_array(&dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
