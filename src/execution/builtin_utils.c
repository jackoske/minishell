/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:43:33 by Jskehan           #+#    #+#             */
/*   Updated: 2024/07/25 17:54:27 by iverniho         ###   ########.fr       */
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

	i = -1;
	while (mini->envp[++i])
	{
		// printf("test1\n");
		ft_putstr_fd(mini->envp[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		// printf("test2\n");
	}
}
int	check_after_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			if (str[i + 1] == '\0')
			{

				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	is_already_exist(char *key, t_mini *mini)
{
	int	i;
	char	**temp;
	char	*temp_key;

	i = 0;
	// printf("key: %s\n", key);
	while (mini->envp[i])
	{
		temp = ft_split(mini->envp[i], '=');
		// printf("is already temp[0]: %s\n", temp[0]);
		if (!temp[0])
			return (1);
		// printf("after check temp[0]: %s\n\n" , temp[0]);
		temp_key = ft_strdup(temp[0]);
		if (ft_strcmp(temp_key, key) == 0)
		{
			free(temp_key);
			ft_free_2d_array(&temp);
			return (1);
		}
		free(temp_key);
		ft_free_2d_array(&temp);
		i++;
	}
	return (0);
}

void	replace_value(char *key, char *value, t_mini *mini)
{
	int	i;
	char	**temp;
	char	*temp_key;
	char	*new_env;

	i = 0;
	while (mini->envp[i])
	{
		temp = ft_split(mini->envp[i], '=');
		if (!temp[0])
			return ;
		temp_key = ft_strdup(temp[0]);
		if (ft_strcmp(temp_key, key) == 0)
		{
			new_env = ft_strjoin(key, ft_strjoin("=", value));
			free(mini->envp[i]);
			mini->envp[i] = new_env;
			free(temp_key);
			ft_free_2d_array(&temp);
			return ;
		}
		free(temp_key);
		ft_free_2d_array(&temp);
		i++;
	}
}

void	mini_export(char **args, t_mini *mini)
{
	char	*key;
	char	*value;
	char	**temp;
	int		len;
	char	*new_env;

	len = ft_2d_array_len(mini->envp);
	if (ft_2d_array_len(args) < 2)
		return ;
	if ((ft_strchr(*(args + 1), '=') == NULL) || (!check_after_equal(*(args + 1))))
	{
		if (is_already_exist(*(args + 1), mini))
		{
			printf("int is exist: %d\n", is_already_exist(*(args + 1), mini));
			return ;
		}
		mini->envp[len] = *(args+1);
		mini->envp[len + 1] = NULL;
		// printf("if no '=' or nothing after '='\n");
		return ;
	}
	temp = ft_split(*(args + 1), '=');
	key = ft_strdup(temp[0]);
	value = ft_strdup(temp[1]);
	if (is_already_exist(key, mini))
	{
		// printf("key already exist\n");
		replace_value(key, value, mini);
		return ;
	}
	ft_free_2d_array(&temp);
	new_env = ft_strjoin(key, ft_strjoin("=", value));
	mini->envp[len] = new_env;
	mini->envp[len + 1] = NULL;
}

// Execute built-in commands
void	execute_builtin(t_mini *mini, t_cmd *cmd)
{
	// printf("cmd->full_command[0]: %s\n", cmd->full_command[0]);

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
