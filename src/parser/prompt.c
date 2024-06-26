/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:09:11 by Jskehan           #+#    #+#             */
/*   Updated: 2024/07/01 18:30:59 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void print_prompt(void)
//{
//	// printf("%s", PROMPT);
//	ft_putstr_fd(PROMPT, 1);
//	rl_on_new_line();
// }

// static int check_command(char *input)
//{
//	if (!quotes_closed(input))
//		return (ft_error(2, NULL), 0);
//	// return (printf("Syntax error\n"), 0);
//	return (1);
// }

// static char *read_command(void)
//{
//	char *input;
//
//	input = readline(PROMPT);
//	if (!check_command(input))
//		return (NULL);
//	if (input != NULL)
//		add_history(input);
//	return (input);
// }

t_list *create_nodes(char **input, t_mini *mini)
{
	t_list *commands;
	t_list *cur_command;
	int i;

	i = -1;
	(void)mini;
	commands = NULL;
	cur_command = NULL;
	while (input && input[++i])
	{
		cur_command = ft_lstlast(commands);
		if (i == 0 || (input[i][0] == '|' && input[i + 1] && input[i + 1][0]))
		{
			ft_lstadd_back(&commands, ft_lstnew(init_cmd()));
			cur_command = ft_lstlast(commands);
		}
		cur_command->content = set_redir(cur_command->content, input[i], input, &i);
		if (i == -2)
		{
			ft_lstclear(&commands, free);
			ft_free_2d_array(&input);
			return (NULL);
		}
	}
	return (commands);
}

int check_tokenized_input(char **tokenizedInput)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while (tokenizedInput && tokenizedInput[++i])
	{
		if (j == 1 && ft_is_special_in_str(tokenizedInput[i]) == 1)
			return (ft_error(6, tokenizedInput[i]), 0);
		// return (printf("%s111\n", NEWLINE_ERR), 0);
		j = ft_is_special_in_str(tokenizedInput[i]);
	}
	return (1);
}

void prompt_loop(t_mini *mini)
{
	char *input;
	char **tokenizedInput;

	tokenizedInput = NULL;
	setup_signal_handlers();
	while (1)
	{
		input = readline(PROMPT);
		if (input == NULL)
		{
			printf("\n");
			break; // Exit the loop if EOF (Ctrl+D) is encountered
		}
		if (input[0] != '\0') // Add non-empty input to history
			add_history(input);
		else
		{
			free(input);
			continue;
		}
		tokenizedInput = ft_remove_quotes(tokenize_input(input, &mini));
		if (!check_tokenized_input(tokenizedInput))
		{
			free(input);
			ft_free_2d_array(&tokenizedInput);
			continue;
		}
		while (*tokenizedInput)
			printf("%s\n", *tokenizedInput++);
		mini->node = create_nodes(tokenizedInput, mini);
		free(input);
	}
}
