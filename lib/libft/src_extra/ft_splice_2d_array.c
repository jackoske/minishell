/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splice_2d_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:55:10 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/09 16:29:28 by iverniho         ###   ########.fr       */
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
char	**ft_splice_2d_array(char **dest, char **src, int n)
{
	char	**temp;
	int		dest_i;
	int		src_i;
	int		total_i;
	int		total_len;

	if (!dest || !dest[0])
	{
		total_len = ft_2d_array_len(src);
		temp = ft_calloc(total_len + 1, sizeof(char *));
		if (!temp)
			return (NULL);
		src_i = -1;
		while (++src_i < total_len)
			temp[src_i] = ft_strdup(src[src_i]);
		return (temp);
	}
	total_len = ft_2d_array_len(dest) + ft_2d_array_len(src);
	dest_i = -1;
	src_i = -1;
	total_i = -1;
	if (n < 0 || n >= ft_2d_array_len(dest))
		return (NULL);
	temp = ft_calloc(total_len + 1, sizeof(char *));
	while (temp && dest[++dest_i])
	{
		if (dest_i != n)
			temp[++total_i] = ft_strdup(dest[dest_i]);
		else
			while (src && src[++src_i])
				temp[++total_i] = ft_strdup(src[src_i]);
	}
	ft_free_2d_array(&dest);
	return (temp);
}
