/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:41:41 by jskehan           #+#    #+#             */
/*   Updated: 2024/06/06 12:31:18 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	int i;

	i = 0;
	if (fd < 0)
		return (0);
	while (s != NULL && *s != '\0')
	{
		i += ft_putchar_fd(*s, fd);
		s++;
	}
	i += ft_putchar_fd('\n', fd);
	return (i);
}
