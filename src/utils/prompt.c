/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:09:11 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/02 17:10:53 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_command_node(char **input, t_list **commands,
		t_list **cur_command, int *i, t_mini *mini)
{
	*cur_command = ft_lstlast(*commands);
	if (*i == 0 || (input[*i][0] == '|' && input[*i + 1] && input[*i + 1][0]))
	{
		ft_lstadd_back(commands, ft_lstnew(init_cmd(mini)));
		*cur_command = ft_lstlast(*commands);
	}
	(*cur_command)->content = set_redir((*cur_command)->content, input[*i],
			input, i);
}

t_list	*create_nodes(char **input, t_mini *mini)
{
	t_list	*commands;
	t_list	*cur_command;
	int		i;

	commands = NULL;
	cur_command = NULL;
	i = -1;
	(void)mini;
	while (input && input[++i])
	{
		handle_command_node(input, &commands, &cur_command, &i, mini);
		if (i == -2)
		{
			ft_lstclear(&commands, free);
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

	i = -1;
	j = 0;
	while (tokenized_input && tokenized_input[++i])
	{
		if (j == 1 && ft_is_special_in_str(tokenized_input[i]) == 1)
			return (ft_error(6, tokenized_input[i]), 0);
		j = ft_is_special_in_str(tokenized_input[i]);
	}
	return (1);
}

void	handle_input(char *input, t_mini *mini)
{
	char	**tokenized_input;
	t_list	*commands;

	tokenized_input = ft_remove_quotes(tokenize_input(input, &mini));
	if (!tokenized_input || !tokenized_input[0]
		|| !check_tokenized_input(tokenized_input))
	{
		free(input);
		if (tokenized_input)
			ft_free_2d_array(&tokenized_input);
		return ;
	}
	commands = create_nodes(tokenized_input, mini);
	if (commands)
		check_to_fork(mini, commands);
	ft_free_2d_array(&tokenized_input);
	free(input);
}

void	prompt_loop(t_mini *mini)
{
	char	*input;

	setup_signal_handlers();
	while (1)
	{
		if (mini->signals.sigint_received)
		{
			mini->signals.sigint_received = 0;
			continue ; // Ensure readline gets called again
		}
		input = readline(PROMPT);
		if (input == NULL)
		{
			printf("\n");
			break ;
		}
		if (input[0] != '\0')
			add_history(input);
		else
		{
			free(input);
			continue ;
		}
		mini->signals.is_executing_command = 1;
		handle_input(input, mini);
		mini->signals.is_executing_command = 0;
	}
}