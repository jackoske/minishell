/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splice_2d_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:16:17 by Jskehan           #+#    #+#             */
/*   Updated: 2024/05/29 14:22:22 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Splices a 2d_arrray into another 2d_arrray at a given index.
 *
 * @param big: The 2d_arrray to splice into.
 * @param small: The 2d_arrray to splice.
 * @param target_index: The index to splice the 2d_arrray at.
 *
 * @return: The spliced 2d_arrray.
 */
char	**ft_splice_2d_arrray(char ***big, char **small, int target_index)
{
	char	**aux;
	int		copy_index;
	int		i;

	copy_index = 0;
	i = 0;
	if (!big || !*big || target_index < 0 || target_index >= ft_2d_array_len(*big))
		return (NULL);
	aux = ft_calloc(ft_2d_array_len(*big) + ft_2d_array_len(small), sizeof(char *));
	if (!aux)
		return (NULL);
	while (big[0][i])
	{
		if (i != target_index)
			ft_copy_2d_array_i(aux, &big[0][i], copy_index);
		else
			ft_copy_2d_array_i(aux, small, copy_index);
		i++;
	}
	ft_free_2d_array(big);
	*big = aux;
	return (*big);
}
