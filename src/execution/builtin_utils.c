/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:43:33 by Jskehan           #+#    #+#             */
/*   Updated: 2024/07/25 16:09:07 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Check if a command is a built-in command
int	is_builtin(t_cmd *cmd)
{
	const char	*builtins[] = {"echo", "pwd", "cd", "export", "unset", "env",
			"exit", "$?"};
	size_t		num_builtins;
	size_t		i;

	i = 0;
	if (!cmd || !cmd->full_command || !cmd->full_command[0])
		return (0);
	num_builtins = sizeof(builtins) / sizeof(builtins[0]);
	while (i < num_builtins)
	{
		if (ft_strcmp(cmd->full_command[0], builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	show_last_command_status(t_mini *mini)
{
	ft_putnbr_fd(mini->exit_status, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	mini_env(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->envp[i])
	{
		ft_putstr_fd(mini->envp[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

void	mini_export(char **args, t_mini *mini)
{
	// int		i;
	char	*key;
	char	*value;
	char	**temp;
	int		len;
	char	*new_env;

	if (ft_2d_array_len(args) < 2)
		return ;
	temp = ft_split(*(args + 1), '=');
	key = ft_strdup(temp[0]);
	value = ft_strdup(temp[1]);
	ft_free_2d_array(&temp);

	// len = ft_strlen(args);
	len = ft_2d_array_len(mini->envp);

	// printf("args: %s\n", args);
	printf("len: %d\n", len);
	new_env = ft_strjoin(key, ft_strjoin("=", value));
	printf("new_env: %s\n", new_env);
	ft_add_row_2d_array(mini->envp, new_env);
	ft_print_2d_array_fd(mini->envp, STDOUT_FILENO);
	printf("last env: %s\n", mini->envp[len - 1]);

}

// Execute built-in commands
void	execute_builtin(t_mini *mini, t_cmd *cmd)
{
	printf("cmd->full_command[0]: %s\n", cmd->full_command[0]);

	// ft_print_2d_array_fd(cmd->full_command, STDOUT_FILENO);

	if (ft_strcmp(cmd->full_command[0], "echo") == 0)
		mini_echo(cmd);
	else if (ft_strcmp(cmd->full_command[0], "pwd") == 0)
		mini_pwd();
	else if (ft_strcmp(cmd->full_command[0], "cd") == 0)
		mini->exit_status = mini_cd(cmd->full_command, mini);
	else if (ft_strcmp(cmd->full_command[0], "exit") == 0)
		mini_exit(cmd->full_command, mini);
	else if (ft_strcmp(cmd->full_command[0], "$?") == 0)
		show_last_command_status(mini);
	else if (ft_strcmp(cmd->full_command[0], "export") == 0)
		mini_export(cmd->full_command, mini);
	// else if (ft_strcmp(cmd->full_command[0], "unset") == 0)
	// 	mini_unset(cmd->full_command, mini);
	else if (ft_strcmp(cmd->full_command[0], "env") == 0)
		mini_env(mini);
	mini->exit_status = 0;
}
