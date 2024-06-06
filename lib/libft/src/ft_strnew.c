/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:21:46 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/08 15:25:15 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
Allocates (with malloc(3)) and returns a
 “fresh” string ending with ’\0’,
*/
char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}
