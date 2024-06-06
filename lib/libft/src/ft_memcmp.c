/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:06:27 by Jskehan           #+#    #+#             */
/*   Updated: 2023/11/22 10:53:59 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = s1;
	p2 = s2;
	while (n-- > 0)
	{
		if (*p1 != *p2)
		{
			return (*p1 - *p2);
		}
		p1++;
		p2++;
	}
	return (0);
}
