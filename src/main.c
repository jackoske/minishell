/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:09:06 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/22 14:15:43 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*g_mini = NULL;

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;

	(void)argc;
	(void)argv;
	mini = malloc(sizeof(t_mini));
	if (!mini)
	{
		perror("Failed to allocate t_mini structure");
		exit(EXIT_FAILURE);
	}
	g_mini = mini;
	initialize_envp(envp);
	init_mini(mini);
	prompt_loop();
	free_mini(&g_mini);
	return (EXIT_SUCCESS);
}
