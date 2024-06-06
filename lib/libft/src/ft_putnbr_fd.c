/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:41:46 by jskehan           #+#    #+#             */
/*   Updated: 2024/06/06 12:20:55 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	long	nbr;
	int 	i;

	i = 0;
	nbr = n;
	if (nbr < 0)
	{
		i += ft_putchar_fd('-', fd);
		nbr = -nbr;
	}
	if (nbr >= 10)
	{
		i += ft_putnbr_fd(nbr / 10, fd);
		i += ft_putchar_fd((nbr % 10) + '0', fd);
	}
	else
		i += ft_putchar_fd(nbr + '0', fd);
	return (i);
}
