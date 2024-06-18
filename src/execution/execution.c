/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:11:43 by Jskehan           #+#    #+#             */
/*   Updated: 2024/06/18 12:39:26 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

//filler
void mini_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->full_command[i])
	{
		ft_putstr_fd(cmd->full_command[i], 1);
		if (cmd->full_command[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	ft_putstr_fd("\n", 1);
	// return (0);
}
//filler
void mini_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free(pwd);
	// return (0);
}	

int	is_builtin(t_cmd *cmd)
{
	(void)cmd;
	// int		l;

	// if (!cmd->full_cmd)
	// 	return (0);
	// if ((cmd->full_cmd && ft_strchr(*cmd->full_cmd, '/')) || (cmd->full_path && 
	// 	ft_strchr(cmd->full_path, '/')))
	// 	return (0);
	// l = ft_strlen(*cmd->full_cmd);
	// if (!ft_strncmp(*cmd->full_cmd, "pwd", l) && l == 3)
	// 	return (1);
	// if (!ft_strncmp(*cmd->full_cmd, "env", l) && l == 3)
	// 	return (1);
	// if (!ft_strncmp(*cmd->full_cmd, "cd", l) && l == 2)
	// 	return (1);
	// if (!ft_strncmp(*cmd->full_cmd, "export", l) && l == 6)
	// 	return (1);
	// if (!ft_strncmp(*cmd->full_cmd, "unset", l) && l == 5)
	// 	return (1);
	// if (!ft_strncmp(*cmd->full_cmd, "echo", l) && l == 4)
	// 	return (1);
	// if (!ft_strncmp(*cmd->full_cmd, "exit", l) && l == 4)
	// 	return (1);
	return (0);
}
//filler
// void	child_builtin(t_mini *mini, t_cmd *cmd, int l)
// {
// 	// signal(SIGINT, SIG_DFL);
// 	// signal(SIGQUIT, SIG_DFL);
// 	if (!is_builtin(cmd) && cmd->full_command)
// 		execve(cmd->command_path, cmd->full_command, mini->envp);
// 	else if (cmd->full_command && !ft_strncmp(*cmd->full_command, "pwd", l) 
// 		&& l == 3)
// 		mini->exit_status = mini_pwd();
// 	else if (is_builtin(cmd) && cmd->full_command && 
// 		!ft_strncmp(*cmd->full_command, "echo", l) && l == 4)
// 		mini->exit_status = mini_echo(cmd);
// 	else if (is_builtin(cmd) && cmd->full_command && 
// 		!ft_strncmp(*cmd->full_command, "env", l) && l == 3)
// 	{
// 		ft_print_2d_array_fd(mini->envp, 1);
// 		mini->exit_status = 0;
// 	}
// }

static void	*child_redir(t_list *command, int fd[2])
{
	t_cmd	*cmd;

	cmd = (t_cmd *)command->content;
	if (cmd->fd_in != STDIN_FILENO)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			return (mini_perror("DUPERR", NULL, 1));
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			return (mini_perror("DUPERR", NULL, 1));
		close(cmd->fd_out);
	}
	else if (command->next && dup2(fd[1], STDOUT_FILENO) == -1)
		return (mini_perror("DUPERR", NULL, 1));
	close(fd[1]);
	return ("");
}

void	*child_process(t_mini *mini, t_list *command, int fd[2])
{
	t_cmd	*cmd;
	int		l;

	cmd = (t_cmd *)command->content;
	l = 0;
	if (cmd->full_command)
		l = ft_strlen(*cmd->full_command);
	child_redir(command, fd);
	close(fd[0]);
	// child_builtin(mini, cmd, l);
	// ft_lstclear(&mini->cmds, free_content);
	(void)l;
	(void)cmd;
	exit(mini->exit_status);
}

void	exec_fork(t_mini *mini, t_list *command, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		mini_perror("FORKERR", NULL, 1);
	}
	else if (!pid)
		child_process(mini, command, fd);
}

void	*check_to_fork(t_mini *mini, t_list *command, int fd[2])
{
	t_cmd	*cmd;
	DIR		*dir;

	cmd = (t_cmd *)command->content;
	dir = NULL;
	if (cmd->full_command)
		dir = opendir(*cmd->full_command);
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
		return (NULL);
	if ((cmd->command_path && access(cmd->command_path, X_OK) == 0) || is_builtin(cmd))
		exec_fork(mini, command, fd);
	else if (!is_builtin(cmd) && ((cmd->command_path && \
		!access(cmd->command_path, F_OK)) || dir))
		mini->exit_status = 126;
	else if (!is_builtin(cmd) && cmd->full_command)
		mini->exit_status = 127;
	if (dir)
		closedir(dir);
	return ("");
}
