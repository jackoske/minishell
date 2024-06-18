/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:09:11 by Jskehan           #+#    #+#             */
/*   Updated: 2024/06/18 17:35:42 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_prompt(void)
{
	printf("%s", PROMPT);
	rl_on_new_line();
}

static int	check_command(char *input)
{
	if (!quotes_closed(input))
		return (printf("Syntax error\n"), 0);
	return (1);
}

static char	*read_command(void)
{
	char	*input;

	input = readline("");
	if (!check_command(input))
		return (NULL);
	if (input != NULL)
		add_history(input);
	return (input);
}

t_list	*create_nodes(char **input, t_mini *mini)
{
	t_list	*commands;
	t_list	*cur_command;
	int		i;

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
		// printf("cur_command->content->fd_out: %d\n", ((t_node *)cur_command->content)->fd_out);
		// printf("cur_command->content->fd_in: %d\n", ((t_node *)cur_command->content)->fd_in);
	}
	return (commands);
}

void	prompt_loop(t_mini *mini)
{
	char	*input;
	char	**tokenizedInput;
	int		i;

	tokenizedInput = NULL;
	while (1)
	{
		print_prompt();
		input = read_command();
		if (input == NULL || input[0] == '\0')
		{
			free(input);
			continue ;
		}
		tokenizedInput = ft_remove_quotes(tokenize_input(input, &mini));
		// printf("tokenizedInput\n");
		// ft_print_2d_array_fd(tokenizedInput, 1);
		mini->node = create_nodes(tokenizedInput, mini);
		i = -1;
		// while (tokenizedInput && tokenizedInput[++i])
		// 	printf("tokenizedInput very last step: %s\n", tokenizedInput[i]);
		free(input);
	}
}
