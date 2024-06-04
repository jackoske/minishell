/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_2d_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:07:30 by Jskehan           #+#    #+#             */
/*   Updated: 2024/05/29 14:11:05 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/**
 * Function: ft_new_2d_array
 * -------------------------
 * Allocates memory for a new 2D array.
 *
 * @param len: The length of the array.
 *
 * @return: A pointer to the new 2D array.
 */
char	**ft_new_2d_array(int len)
{
	char	**out;

	out = malloc(sizeof(char *) * len);
	if (!out)
		return (NULL);
	return (out);
}
