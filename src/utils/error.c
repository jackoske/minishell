/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:06:08 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/04 17:17:24 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void *mini_perror(char *str, char *str2, int fd)
{
	// ditry hack to see whats going on :-)
	// perror("fuuu");
	fd = 2;
	ft_putstr_fd("minishell> ", fd);
	ft_putstr_fd(str, fd);
	if (str2)
	{
		ft_putstr_fd(": ", fd);
		ft_putstr_fd(str2, fd);
	}
	ft_putstr_fd("\n", fd);
	// to do
	return (NULL);
}
