/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:11:01 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/23 13:07:10 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(const char *token)
{
	if (!token)
		return (0);
	if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0 \
		|| ft_strcmp(token,
			"<") == 0 || ft_strcmp(token, "<<") == 0)
		return (1);
	return (0);
}
