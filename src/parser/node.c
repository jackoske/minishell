/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:21:00 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/09 17:41:23 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_command_node(char **input, t_list **commands,
		t_list **cur_command, int *i)
{
	*cur_command = ft_lstlast(*commands);
	if (*i == 0 || (input[*i][0] == '|' && input[*i + 1] && input[*i + 1][0]))
	{
		ft_lstadd_back(commands, ft_lstnew(init_cmd()));
		*cur_command = ft_lstlast(*commands);
	}
	(*cur_command)->content = set_redir((*cur_command)->content, input[*i],
			input, i);
	if (!(*cur_command)->content)
		return (ft_lstclear(commands, free), -1);
	return (1);
}

t_list	*create_nodes(char **input)
{
	t_list	*commands;
	t_list	*cur_command;
	int		i;

	commands = NULL;
	cur_command = NULL;
	i = -1;
	while (input && input[++i])
	{
		if (handle_command_node(input, &commands, &cur_command, &i) == -1)
		{
			return (g_mini->exit_status = 1, NULL);
		}
		if (i == -2)
		{
			ft_lstclear(&commands, free_cmd);
			ft_free_2d_array(&input);
			return (NULL);
		}
	}
	return (commands);
}
