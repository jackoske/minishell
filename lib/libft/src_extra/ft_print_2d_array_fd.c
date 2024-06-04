/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_2d_array_fd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:21:48 by Jskehan           #+#    #+#             */
/*   Updated: 2024/05/28 17:24:46 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int ft_print_2d_array_fd(char **array, int fd)
{
	int i;

	i = 0;
	while (array && array[i])
	{
		ft_putendl_fd(array[i], fd);
		i++;
	}
	return (i);
}
