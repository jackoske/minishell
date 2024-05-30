/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 17:36:11 by aperez-b          #+#    #+#             */
/*   Updated: 2024/05/29 18:08:14 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;

	if (nmemb <= 0 || size <= 0)
		str = (char *)malloc(1);
	else
		str = (char *)malloc(nmemb * size);
	if (!str)
		return (NULL);
	return (ft_memset(str, 0, nmemb * size));
}
