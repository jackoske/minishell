/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:09:11 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/09 16:20:17 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_command_node(char **input, t_list **commands,
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

int	check_tokenized_input(char **tokenized_input)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	j = 0;
	while (tokenized_input && tokenized_input[++i])
	{
		len = ft_strlen(tokenized_input[i]) - 1;
		if (j == 1 && is_special_char_input(tokenized_input[i][len]) == 1 && \
				is_string_quoted(tokenized_input[i]) != 1)
			return (ft_error(6, tokenized_input[i]), 0);
		j = is_special_char_input(tokenized_input[i][len]);
		if (tokenized_input[i][0] == '|')
			j = 0;
	}
	return (1);
}

void	handle_input(char *input)
{
	char	**tokenized_input;
	t_list	*commands;

	tokenized_input = tokenize_input(input);
	if (!tokenized_input || !tokenized_input[0] \
		|| !check_tokenized_input(tokenized_input))
	{
		free(input);
		if (tokenized_input)
			ft_free_2d_array(&tokenized_input);
		return ;
	}
	commands = create_nodes(tokenized_input);
	if (commands)
	{
		check_to_fork(commands);
		ft_lstclear(&commands, free_cmd);
	}
	ft_free_2d_array(&tokenized_input);
	free(input);
}

void	prompt_loop(void)
{
	char	*input;

	setup_signal_handlers();
	while (1)
	{
		if (g_mini->signals.sigint_received)
		{
			g_mini->signals.sigint_received = 0;
			continue ;
		}
		input = readline(PROMPT);
		if (input == NULL)
			break ;
		if (input[0] != '\0')
			add_history(input);
		else
		{
			free(input);
			continue ;
		}
		g_mini->signals.is_executing_command = 1;
		handle_input(input);
		g_mini->signals.is_executing_command = 0;
	}
}
