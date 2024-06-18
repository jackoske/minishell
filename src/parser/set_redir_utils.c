/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:44:29 by iverniho          #+#    #+#             */
/*   Updated: 2024/06/18 17:35:52 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
for '<'
no such file or directory
F_OK == -1
or
permission denied
R_OK == -1

for '>'
permission denied
W_OK == -1

for '>>'
permission denied
W_OK == -1
*/

static int	check_access(char *path, int mode)
{
	// printf("accces F inside check: %d\n", access(path, F_OK));
	// printf("accces R inside check: %d\n", access(path, R_OK));
	// printf("accces W inside check: %d\n", access(path, W_OK));
	if (mode == 1)
	{
		if (access(path, F_OK) == -1)
			return (printf("no such file or directory\n"), 0);
		else if (access(path, R_OK) == -1)
			return (printf("permission denied\n"), 0);
		return (printf("permission granted\n"), 1);
	}
	else if (mode == 2)
	{
		if (access(path, W_OK) == -1 && access(path, F_OK) != -1)
			return (printf("permission denied\n"), 0);
		return (printf("permission granted\n"), 1);
	}
	return (1);
}

static t_cmd	*get_redir_out(t_cmd *node, char *input, char **full_command, int **i)
{
	if (node->fd_out > 2)
		close(node->fd_out);
	if (!input)
	{
		node->fd_out = -1;
		return (node);
	}
	// ft_print_2d_array_fd(full_command, 1);
	// printf("full_command[(*(*i))]: %s\n", full_command[(*(*i))]);
	++(*(*i));
	// printf("full_command[(*(*i))]: %s\n", full_command[(*(*i))]);

	if (!full_command[(*(*i))])
	{
		**i = -2;
		node->fd_out = -1;
		return (printf("%s\n", NEWLINE_ERR), node);
	}
	if (!check_access(full_command[(*(*i))], 2))
	{
		node->fd_out = -1;
		return (node);
	}
	// printf("node->fd_out: %d\n", node->fd_out);
	node->fd_out = open(full_command[(*(*i))], O_WRONLY | O_CREAT | O_TRUNC, 0666);

	// printf("after\nnode->fd_out: %d\n", node->fd_out);
	return (node);
}

static t_cmd	*get_append_out(t_cmd *node, char *input, char **full_command, int **i)
{
	if (node->fd_out > 2)
		close(node->fd_out);
	if (!input)
	{
		node->fd_out = -1;
		return (node);
	}
	++(*(*i));
	// if (ft_is_special_symbol(full_command[(*(*i))][0]))
	if (ft_is_special_in_str(full_command[(*(*i))]))
	{
		printf("%s `%s'\n", SYNTAX_ERR, full_command[(*(*i))]);
		**i = -2;
		node->fd_out = -1;
		return (node);
	}
	printf("full_command[(*(*i))]: %s\n", full_command[(*(*i))]);
	if (!full_command[(*(*i))] /*|| ft_is_special_symbol(full_command[(*(*i))][0])*/)
	{
		**i = -2;
		node->fd_out = -1;
		return (printf("%s `newline'\n", SYNTAX_ERR), node);
	}
	if (!check_access(full_command[(*(*i))], 2))
	{
		node->fd_out = -1;
		return (node);
	}
	// printf("node->fd_out: %d\n", node->fd_out);

	node->fd_out = open(full_command[(*(*i))], O_WRONLY | O_CREAT | O_APPEND, 0666);
	// printf("end of get_append_out\n");
	// if (full_command[])
	// printf("full_command[(*(*i))]: %s\n", full_command[(*(*i))]);
	// printf("full_command[++(*(*i))]: %s\n", full_command[++(*(*i))]);
	// printf("after\nnode->fd_out: %d\n", node->fd_out);
	return (node);
}

static t_cmd	*get_redir_heredoc(t_cmd *node, char *input, char **full_command, int **i)
{
	(void)input;
	(void)full_command;
	(void)i;
	return (node);
}

static t_cmd	*get_redir_in(t_cmd *node, char *input, char **full_command, int **i)
{
	if (!input)
	{
		node->fd_out = -1;
		return (node);
	}
	++(*(*i));
	if (!full_command[(*(*i))])
	{
		**i = -2;
		node->fd_in = -1;
		return (printf("%s\n", NEWLINE_ERR), node);
	}
	if (!check_access(full_command[(*(*i))], 1))
	{
		node->fd_in = -1;
		return (node);
	}
	// printf("node->fd_in: %d\n", node->fd_in);
	node->fd_in = open(full_command[(*(*i))], O_RDONLY);
	// printf("after\nnode->fd_in: %d\n", node->fd_in);
	return (node);
}
t_cmd	*set_redir(t_cmd *node, char *input, char **full_command, int *i)
{
	if (input[0])
	{
		// printf("input: %s\n", input);
		if (input[0] == '>' && input[1] == '>')
			node = get_append_out(node, input, full_command, &i);
		else if (input[0] == '>')
			node = get_redir_out(node, input, full_command, &i);
		else if (input[0] == '<' && input[1] == '<')
			node = get_redir_heredoc(node, input, full_command, &i);
		else if (input[0] == '<')
			node = get_redir_in(node, input, full_command, &i);
		else if (input[0] != '|')
			node->full_command = ft_add_row_2d_array(node->full_command, input);
	}
	// printf("end of set_redir\n");
	return (node);
}
