/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:41:41 by jskehan           #+#    #+#             */
/*   Updated: 2024/08/09 16:24:11 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	int	i;

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
