/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:08:23 by Jskehan           #+#    #+#             */
/*   Updated: 2024/06/18 12:39:45 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_fd(int oldfd, t_cmd *cmd, char *path)
{
	int	fd;

	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	if (access(path, F_OK) == -1 && !cmd->is_outfile)
		mini_perror("NDIR", path, 127);
	else if (!cmd->is_outfile && access(path, R_OK) == -1)
		mini_perror("NPERM", path, 126);
	else if (cmd->is_outfile && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		mini_perror("NPERM", path, 126);
	if (cmd->is_outfile && cmd->is_append)
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (cmd->is_outfile && !cmd->is_append)
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!cmd->is_outfile && oldfd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}

t_mini	*get_file(t_mini *mini, t_list *command, char **args, int *i)
{
	char	*nl;
	t_cmd	*cmd;

	cmd = (t_cmd *)command->content;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[*i])
	{
		if (cmd->is_outfile)
			cmd->fd_out = get_fd(cmd->fd_out, cmd, args[*i]);
		else
			cmd->fd_in = get_fd(cmd->fd_in, cmd, args[*i]);
	}
	if (!args[*i] || (cmd->is_outfile ? cmd->fd_out : cmd->fd_in) == -1)
	{
		*i = -1;
		if ((cmd->is_outfile ? cmd->fd_out : cmd->fd_in) != -1)
		{
			ft_putendl_fd(nl, 2);
			mini->exit_status = 2;
		}
		else
			mini->exit_status = 1;
	}
	return (mini);
}

t_mini	*handle_here_doc(t_mini *mini, t_list *command, char **args, int *i)
{
	char	*aux[2];
	char	*nl;
	char	*warn;
	t_cmd	*cmd;

	cmd = (t_cmd *)command->content;
	warn = "minishell: warning: here-document delimited by end-of-file";
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[++(*i)])
	{
		aux[0] = args[*i];
		cmd->fd_in = get_here_doc(mini, warn);
	}
	if (!args[*i] || cmd->fd_in == -1)
	{
		*i = -1;
		if (cmd->fd_in != -1)
		{
			ft_putendl_fd(nl, 2);
			mini->exit_status = 2;
		}
	}
	(void)aux;
	return (mini);
}
