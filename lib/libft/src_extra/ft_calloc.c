/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:20:39 by Jskehan           #+#    #+#             */
/*   Updated: 2024/06/06 16:38:52 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	str = (char *)malloc(nmemb * size);
	if (!str)
		return (NULL);
	return (ft_memset(str, 0, nmemb * size));
}
