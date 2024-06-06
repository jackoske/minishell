/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:52:09 by Jskehan           #+#    #+#             */
/*   Updated: 2023/11/22 17:34:27 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *p, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	value;

	ptr = (unsigned char *)p;
	value = (unsigned char)c;
	while (n--)
		*ptr++ = value;
	return (p);
}
