/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:11:01 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/19 12:11:09 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(const char *token)
{
	if (!token)
		return (0);
	if (strcmp(token, ">") == 0 || strcmp(token, ">>") == 0 || strcmp(token,
			"<") == 0 || strcmp(token, "<<") == 0)
		return (1);
	return (0);
}
