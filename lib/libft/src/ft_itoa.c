/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jskehan <jskehan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:15:09 by Jskehan           #+#    #+#             */
/*   Updated: 2023/11/29 23:07:32 by jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	numberlength(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long long	num;
	int			numlen;
	int			neg;
	char		*str;

	num = n;
	neg = 0;
	if (num < 0)
	{
		neg += 1;
		num *= -1;
	}
	numlen = numberlength(num);
	str = (char *)malloc((numlen + 1 + neg));
	if (!str)
		return (NULL);
	str[numlen + neg] = '\0';
	while (numlen--)
	{
		str[numlen + neg] = (num % 10) + '0';
		num /= 10;
	}
	if (neg)
		str[0] = '-';
	return (str);
}
