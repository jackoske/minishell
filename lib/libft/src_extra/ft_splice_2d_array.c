/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splice_2d_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:55:10 by Jskehan           #+#    #+#             */
/*   Updated: 2024/06/06 12:43:25 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
 * Splices a 2d_arrray into another 2d_arrray at a given index.
 *
 * @param dest: The 2d_arrray to splice into.
 * @param src: The 2d_arrray to splice.
 * @param target_index: The index to splice the 2d_arrray at.
 * @return: The spliced 2d_arrray. NULL if the operation fails.
 * Note: The function frees the original 2d_arrray. if succesful
 * Note: NULL if i > dest_len or i < 0
 */
char	**ft_splice_2d_array(char ***big, char **small, int n)
{
	char	**temp;
	int		big_i;
	int		small_i;
	int		total_i;

	big_i = -1;
	small_i = -1;
	total_i = -1;
	if (!big || !*big || n < 0 || n >= ft_2d_array_len(*big))
		return (NULL);
	temp = ft_calloc(ft_2d_array_len(*big) + ft_2d_array_len(small),
			sizeof(char *));
	while (temp && big[0][++big_i])
	{
		if (big_i != n)
			temp[++total_i] = ft_strdup(big[0][big_i]);
		else
			while (small && small[++small_i])
				temp[++total_i] = ft_strdup(small[small_i]);
	}
	ft_free_2d_array(big);
	*big = temp;
	return (*big);
}
