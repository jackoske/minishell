/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:23:01 by Jskehan           #+#    #+#             */
/*   Updated: 2023/11/22 17:45:02 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	const char		*s;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (const char *)src;
	if (dst <= src)
	{
		while (n--)
			*d++ = *s++;
	}
	else if (dst > src)
	{
		d += n - 1;
		s += n - 1;
		while (n--)
			*d-- = *s--;
	}
	return (dst);
}
