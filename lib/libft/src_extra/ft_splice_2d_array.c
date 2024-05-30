/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splice_2d_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:55:10 by Jskehan           #+#    #+#             */
/*   Updated: 2024/05/30 23:55:57 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	copy_arrays_to_new(char **new, char **dest, char **src, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (dest[j] && j < i)
	{
		new[j] = ft_strdup(dest[j]);
		j++;
	}
	while (src[k])
	{
		new[j] = ft_strdup(src[k]);
		j++;
		k++;
	}
	k = i;
	while (dest[k])
	{
		new[j] = ft_strdup(dest[k]);
		j++;
		k++;
	}
	new[j] = NULL;
}

/*
 * Splices a 2d_arrray into another 2d_arrray at a given index.
 *
 * @param dest: The 2d_arrray to splice into.
 * @param src: The 2d_arrray to splice.
 * @param target_index: The index to splice the 2d_arrray at.
 * @return: The spliced 2d_arrray.
 */
char	**ft_splice_2d_array(char **dest, char **src, int i)
{
	char	**new;

	if (!dest || !src || i < 0)
		return (NULL);
	new = (char **)malloc(sizeof(char *) * (ft_2d_array_len(dest)
				+ ft_2d_array_len(src) + 1));
	if (!new)
		return (NULL);
	copy_arrays_to_new(new, dest, src, i);
	return (new);
}
