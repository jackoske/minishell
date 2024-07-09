/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:34:53 by Jskehan           #+#    #+#             */
/*   Updated: 2024/07/03 16:35:07 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//not used but maybe used later!
void free_mini(t_mini *mini)
{
    if (mini->current_dir != NULL)
        free(mini->current_dir);
    if (mini->envp != NULL)
        ft_free_2d_array(&mini->envp);
    if (mini->node != NULL)
        ft_lstclear(&mini->node, free);
    free(mini);
}
