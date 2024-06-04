/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_2d_array_i.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:20:27 by Jskehan           #+#    #+#             */
/*   Updated: 2024/06/04 13:00:55 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
 * Copies a 2d_arrray into another 2d_arrray at a given index.
 * . (disregards whats at index and after)
 * (maybe we need splice instead)
 * @param dest: The destination 2d_arrray.
 * @param src: The source 2d_arrray.
 * @param index: The index to copy the 2d_arrray at.
 */
void	ft_copy_2d_array_i(char **dest, char **src, int index)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		dest[index++] = ft_strdup(src[i]);
		i++;
	}
}
