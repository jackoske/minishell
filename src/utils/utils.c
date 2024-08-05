/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:34:53 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/04 17:11:32 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// not used but maybe used later!
void	free_mini(t_mini *mini)
{
	if (mini->current_dir != NULL)
		free(mini->current_dir);
	if (mini->envp != NULL)
		ft_free_2d_array(&mini->envp);
	if (mini->node != NULL)
		ft_lstclear(&mini->node, free);
	free(mini);
}

int	is_all_num(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}
