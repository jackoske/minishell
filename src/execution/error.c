/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:06:08 by Jskehan           #+#    #+#             */
/*   Updated: 2024/06/14 16:00:29 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*mini_perror(char *str, char *str2, int fd)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(str, fd);
	if (str2)
	{
		ft_putstr_fd(": ", fd);
		ft_putstr_fd(str2, fd);
	}
	ft_putstr_fd("\n", fd);
	//to do
	return (NULL);
}
