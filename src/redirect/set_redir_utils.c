/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:23:13 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/06 17:10:09 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Error handling for file access:
- '<' : no such file or directory (F_OK == -1) or permission denied (R_OK == -1)
- '>' : permission denied (W_OK == -1)
- '>>': permission denied (W_OK == -1)
*/
static int check_access(char *path, int mode)
{
	if (mode == 1) // Read mode
	{
		if (access(path, F_OK) == -1)
		{
			ft_error_with_exit(3, NULL, 0, NULL);
			return (0);
		}
		else if (access(path, R_OK) == -1)
			return (ft_error_with_exit(5, NULL, 1, NULL), 0);
		return (1);
	}
	else if (mode == 2) // Write mode
	{
		if (access(path, W_OK) == -1 && access(path, F_OK) != -1)
			return (ft_error_with_exit(5, NULL, 1, NULL), 0);
		return (1);
	}
	return (1);
}

static int get_fd(int oldfd, int mode, char *path)
{
	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	if (!check_access(path, mode))
		return (-1);
	if (mode == 1)
		return (open(path, O_RDONLY));
	else if (mode == 2)
		return (open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666));
	else if (mode == 3)
		return (open(path, O_WRONLY | O_CREAT | O_APPEND, 0666));
	return (-1);
}

static t_cmd *handle_redirection(t_cmd *node, char **full_command, int **i,
								 int mode)
{
	if (mode == 2 || mode == 3)
	{
		if (node->fd_out > 2)
			close(node->fd_out);
		node->fd_out = get_fd(node->fd_out, mode, full_command[++(**i)]);
		if (!full_command[*(*i)] || node->fd_out == -1)
		{
			**i = -2;
			if (node->fd_out != -1)
				g_mini->exit_status = 2;
			else
				g_mini->exit_status = 1;
		}
	}
	else if (mode == 1)
	{
		if (node->fd_in > 2)
			close(node->fd_in);
		node->fd_in = get_fd(node->fd_in, mode, full_command[++(**i)]);
		if (node->fd_in == -1)
			**i = -2;
	}
	return (node);
}

static t_cmd *get_redir_heredoc(t_cmd *node,
								char **full_command, int **i)
{
	if (!full_command[++(**i)])
	{
		**i = -2;
		node->fd_in = -1;
		ft_error(1, NULL);
		return (node);
	}
	node->fd_in = get_here_doc(full_command[(*(*i))],
							   "minishell: warning: here-document delimited by end-of-file");
	if (node->fd_in == -1)
	{
		**i = -2;
		node->fd_in = -1;
	}
	node->is_heredoc = 1;
	return (node);
}

char *remove_1st_and_last_el(char *str)
{
	char *new_str;
	int i;

	i = 0;
	new_str = ft_calloc(ft_strlen(str) - 1, sizeof(char));
	if (!new_str)
		return (NULL);
	while (i++ < (int)ft_strlen(str) - 2)
		new_str[i - 1] = str[i];
	new_str[i - 1] = '\0';
	return (new_str);
}

char *remove_paired_quotes(char *str) {
	int i = 0,
	j = 0;
	int single_quote_open = 0,
	double_quote_open = 0;

	while (str[i]) {
		if (str[i] == '\'' && !double_quote_open) {
			single_quote_open = !single_quote_open;
		} else if (str[i] == '\"' && !single_quote_open) {
			double_quote_open = !double_quote_open;
		} else {
			str[j++] = str[i];
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

t_cmd *set_redir(t_cmd *node, char *input, char **full_command, int *i)
{
	if (input[0])
	{
		// printf("input[0] = %c\n", input[0]);
		if (input[0] == '>' && input[1] == '>')
			node = handle_redirection(node, full_command, &i, 3); // Append
		else if (input[0] == '>')
			node = handle_redirection(node, full_command, &i, 2); // Truncate
		else if (input[0] == '<' && input[1] == '<')
			node = get_redir_heredoc(node, full_command, &i); // Heredoc
		else if (input[0] == '<')
			node = handle_redirection(node, full_command, &i, 1); // Input
		else if (input[0] != '|')
		{
			if (!is_string_quoted(input))
				node->full_command = ft_add_row_2d_array(node->full_command, input, 0);
			else
				node->full_command = ft_add_row_2d_array(node->full_command, remove_paired_quotes(input), 0);
		}
	}
	if (node->fd_in == -1 || node->fd_out == -1)
	{
		ft_free_2d_array(&node->full_command);
		free(node);
		return (NULL);
	}
	return (node);
}
