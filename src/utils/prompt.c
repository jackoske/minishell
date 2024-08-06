/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:09:11 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/06 17:28:33 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_string_quoted(char *str)
{
	int single_quote_open;
	int double_quote_open;
	int has_quotes;

	single_quote_open = double_quote_open = has_quotes = 0;
	while (*str) {
		if (*str == '\'' && !double_quote_open) {
			single_quote_open = !single_quote_open;
			has_quotes = 1;
		} else if (*str == '\"' && !single_quote_open) {
			double_quote_open = !double_quote_open;
			has_quotes = 1;
		}
		str++;
	}
	if (single_quote_open || double_quote_open) {
		return -1;
	}
	if (!has_quotes) {
		return 0;
	}
	return 1;
}


int	handle_command_node(char **input, t_list **commands,
		t_list **cur_command, int *i)
{
	// char	*temp;
	// int		j;
	// char	*aux;

	// j = -1;
	// printf("inside handle_command_node\n");
	// ft_print_2d_array_fd(input, 1);
	*cur_command = ft_lstlast(*commands);
	if (*i == 0 || (input[*i][0] == '|' && input[*i + 1] && input[*i + 1][0]))
	{
		ft_lstadd_back(commands, ft_lstnew(init_cmd()));
		*cur_command = ft_lstlast(*commands);
	}
	// printf("input[*i]: %s\n", input[*i]);
	// if (!is_string_quoted(input[*i]))
	// {
	// 	// while (temp && temp[++j])
	// 	// {
	// 	// 	aux = ft_trimm_quotes(temp[j], 0, 0);
	// 	// 	free(temp[j]);
	// 	// 	temp[j] = aux;
	// 	// }
	// 	(*cur_command)->content = set_redir((*cur_command)->content, input[*i],
	// 		input, i);

	// }
	(*cur_command)->content = set_redir((*cur_command)->content, input[*i],
			input, i);
	// printf("current command: %s\n", (char *)(*cur_command)->content);
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
		// printf("test\n");

		if (handle_command_node(input, &commands, &cur_command, &i) == -1)
		{
			// printf("test4\n");
			return (g_mini->exit_status = 1, NULL);
		}
		if (i == -2)
		{
			// printf("test2\n");
			ft_lstclear(&commands, free_cmd);
			ft_free_2d_array(&input);
			return (NULL);
		}
		// printf("test3\n");
	}
	// printf("test4\n");
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
		// printf("tokenized_input[%d]: %s\n", i, tokenized_input[i]);
		// printf("j before: %d\n", j);
		if (j == 1 && ft_is_special_in_str(tokenized_input[i]) == 1 && is_string_quoted(tokenized_input[i]) == 1)
			return (ft_error(6, tokenized_input[i]), 0);
		j = ft_is_special_in_str(tokenized_input[i]);
		// printf("j after: %d\n", j);
	}
	return (1);
}

void	handle_input(char *input)
{
	char	**tokenized_input;
	t_list	*commands;

	tokenized_input = tokenize_input(input);
	// tokenized_input = ft_remove_quotes(tokenize_input(input));

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
