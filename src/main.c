/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:09:06 by Jskehan           #+#    #+#             */
/*   Updated: 2024/07/19 13:46:45 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **envp)
{
	int		i;
	char	**new_envp;

	for (i = 0; envp[i]; i++)
		;
	new_envp = malloc((i + 1) * sizeof(char *));
	if (!new_envp)
		return (NULL);
	for (i = 0; envp[i]; i++)
	{
		new_envp[i] = strdup(envp[i]);
		if (!new_envp[i])
		{
			// Free previously allocated memory in case of failure
			while (i--)
				free(new_envp[i]);
			free(new_envp);
			return (NULL);
		}
	}
	new_envp[i] = NULL;
	return (new_envp);
}

void	initialize_envp(t_mini **mini, char **envp)
{
	char	cwd[PATH_MAX];
	char	*shlvl_str;
	int		shlvl;

	*mini = malloc(sizeof(t_mini));
	if (!*mini)
	{
		perror("Failed to allocate t_mini structure");
		exit(EXIT_FAILURE);
	}
	(*mini)->envp = copy_env(envp);
	if (!(*mini)->envp)
	{
		// Handle memory allocation failure
		perror("Failed to initialize environment variables");
		exit(EXIT_FAILURE);
	}
	// Set any additional required environment variables
	if (getcwd(cwd, sizeof(cwd)))
	{
		(*mini)->envp = ft_setenv("PWD", cwd, (*mini)->envp, 1);
		if (!(*mini)->envp)
		{
			perror("Failed to set PWD environment variable");
			exit(EXIT_FAILURE);
		}
	}
	(*mini)->envp = ft_setenv("SHELL", "jackoshell", (*mini)->envp, 1);

	// Handle SHLVL
	shlvl_str = ft_getenv("SHLVL", (*mini)->envp, strlen("SHLVL"));
	if (shlvl_str)
	{
		shlvl = atoi(shlvl_str) + 1;
	}
	else
	{
		shlvl = 1;
	}
	char shlvl_value[12];
	snprintf(shlvl_value, sizeof(shlvl_value), "%d", shlvl);
	(*mini)->envp = ft_setenv("SHLVL", shlvl_value, (*mini)->envp, 1);
}

t_cmd	*init_cmd(t_mini *mini)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->full_command = NULL;
	node->command_path = NULL;
	node->fd_in = 0;
	node->fd_out = 1;
	node->is_heredoc = 0;
	node->is_append = 0;
	node->mini = mini;
	return (node);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;

	(void)argc;
	(void)argv;
	initialize_envp(&mini, envp);
	setup_signal_handlers();
	//--------------TESTING----------------
	// test_exec();
	// test_heredoc();
	// libft_extra_tester();
	//--------------!TESTING----------------
	printf("%s\n", MINISHELL_ASCII);
	prompt_loop(mini);
	// char *str = get_next_line(0);
	// printf("%s\n", str);
	// free(str);
	for (int i = 0; mini->envp[i]; i++)
		free(mini->envp[i]);
	free(mini->envp);
	free(mini);
	return (EXIT_SUCCESS);
}
