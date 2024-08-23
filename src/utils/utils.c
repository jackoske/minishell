/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:34:53 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/23 12:46:25 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to free a t_cmd structure
void	free_cmd(void *cmd_ptr)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmd_ptr;
	if (cmd->full_command)
		ft_free_2d_array(&(cmd->full_command));
	if (cmd->command_path)
		free(cmd->command_path);
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	free(cmd);
}

// not used but maybe used later!
void	free_mini(t_mini **mini)
{
	if ((*mini)->current_dir != NULL)
		free((*mini)->current_dir);
	if ((*mini)->envp != NULL)
		ft_free_2d_array(&(*mini)->envp);
	if ((*mini)->node != NULL)
		ft_lstclear(&(*mini)->node, free_cmd);
	free(*mini);
	*mini = NULL;
}

int	is_all_num(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

// int	is_string_quoted(const char *str)
// {
// 	int	single_quote_open;
// 	int	double_quote_open;
// 	int	has_quotes;

// 	single_quote_open = ((double_quote_open = 0), (has_quotes = 0), 0);
// 	while (*str)
// 	{
// 		if (*str == '\'' && !double_quote_open)
// 		{
// 			single_quote_open = !single_quote_open;
// 			has_quotes = 1;
// 		}
// 		else if (*str == '\"' && !single_quote_open)
// 		{
// 			double_quote_open = !double_quote_open;
// 			has_quotes = 1;
// 		}
// 		str++;
// 	}
// 	if (single_quote_open || double_quote_open)
// 		return (-1);
// 	if (!has_quotes)
// 		return (0);
// 	return (1);
// }

int	is_special_char_input(char c)
{
	char	*prohibited_chars;

	prohibited_chars = "|<>";
	while (*prohibited_chars)
	{
		if (c == *prohibited_chars)
			return (1);
		prohibited_chars++;
	}
	return (0);
}
