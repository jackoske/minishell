/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:43:48 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/21 17:43:54 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_unset(char **args)
{
	int		i;
	char	**new_env_arr;
	int		j;

	if (ft_2d_array_len(args) < 2)
		return ;
	i = -1;
	j = 0;
	new_env_arr = ft_calloc(ft_2d_array_len(g_mini->envp), sizeof(char *));
	if (!new_env_arr)
		return ;
	while (g_mini->envp[++i])
	{
		if (ft_strncmp(g_mini->envp[i], args[1], ft_strlen(args[1])) != 0)
			new_env_arr[j++] = ft_strdup(g_mini->envp[i]);
	}
	new_env_arr[j] = NULL;
	ft_free_2d_array(&g_mini->envp);
	g_mini->envp = new_env_arr;
}
