/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:09:11 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/05 19:02:06 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_string_quoted(char *str)
{
	int i;
	int quote[2];

	i = 0;
	quote[0] = 0;
	quote[1] = 0;
	while (str[i])
	{
		quote[0] = (quote[0] + (!quote[1] && str[i] == '\'')) % 2;
		quote[1] = (quote[1] + (!quote[0] && str[i] == '\"')) % 2;
		i++;
	}
	return (quote[0] || quote[1]);

}

int	handle_command_node(char **input, t_list **commands,
		t_list **cur_command, int *i)
{
	// printf("input: %s\n", input[*i]);
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
			return (g_mini->exit_status = 1, NULL);
		if (i == -2)
		{
			ft_lstclear(&commands, free_cmd);
			ft_free_2d_array(&input);
			return (NULL);
		}
	}
	// print_nodes(commands);
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

void	handle_input(char *input)
{
	char	**tokenized_input;
	t_list	*commands;

	tokenized_input = ft_remove_quotes(tokenize_input(input));
	if (!tokenized_input || !tokenized_input[0]
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

void	prompt_loop()
{
	char	*input;

	setup_signal_handlers();
	while (1)
	{
		if (g_mini->signals.sigint_received)
		{
			g_mini->signals.sigint_received = 0;
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
		g_mini->signals.is_executing_command = 1;
		handle_input(input);
		g_mini->signals.is_executing_command = 0;
	}
}
