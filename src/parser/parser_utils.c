/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:38:35 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/05 16:32:33 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_word_count_quotes(char *input)
{
	int		i;
	int		count;
	char	quote;

	quote = ((i = 0), (count = 0), 0);
	while (input[i])
	{
		if (ft_is_space(input[i]))
		{
			while (ft_is_space(input[i]))
				i++;
			if (!quote)
				count++;
		}
		else
		{
			if ((input[i] == '\"' || input[i] == '\'') && quote == input[i])
				quote = 0;
			else if ((input[i] == '\"' || input[i] == '\''))
				quote = input[i];
			i++;
		}
	}
	return (count + 1);
}

int	count_unescaped_quotes(char const *s1)
{
	int	count;
	int	i;
	int	d_quote;
	int	s_quote;

	i = 0;
	count = 0;
	d_quote = 0;
	s_quote = 0;
	while (s1 && s1[i])
	{
		s_quote = (s_quote + (!d_quote && s1[i] == '\'')) % 2;
		d_quote = (d_quote + (!s_quote && s1[i] == '\"')) % 2;
		if ((s1[i] == '\"' && !s_quote) || (s1[i] == '\'' && !d_quote))
			count++;
		i++;
	}
	if (s_quote || d_quote)
		return (-1);
	return (count);
}

static char	*ft_trimm_quotes(char const *s1, int s_quote, int d_quote)
{
	int		unescaped_quotes;
	char	*trimmed;
	int 	i;

	i = -1;
	unescaped_quotes = count_unescaped_quotes(s1);
	if (!s1 || unescaped_quotes == -1)
		return (NULL);
	trimmed = ft_calloc(ft_strlen(s1) - unescaped_quotes + 1, sizeof(char));
	if (!trimmed)
		return (NULL);
	while (*s1)
	{
		s_quote = (s_quote + (!d_quote && *s1 == '\'')) % 2;
		d_quote = (d_quote + (!s_quote && *s1 == '\"')) % 2;
		if ((*s1 != '\"' || s_quote) && (*s1 != '\'' || d_quote) \
			&& ++i >= 0)
			trimmed[i] = *s1;
		s1++;
	}
	trimmed[++i] = '\0';
	return (trimmed);
}

char	**ft_remove_quotes(char **tokenizedInput)
{
	char	**temp;
	char	*aux;
	int		i;

	i = -1;
	temp = ft_duplicate_2d_array(tokenizedInput);
	while (temp && temp[++i])
	{
		aux = ft_trimm_quotes(temp[i], 0, 0);
		free(temp[i]);
		temp[i] = aux;
	}
	// i = -1;
	// while (temp && temp[++i])
	// {
	// 	if (ft_is_special_in_str(temp[i]) && ft_is_special_in_str(temp[i++]))
	// 		return (NULL);

	// }
	return (temp);
}

static char	*add_quotes(char *str)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	j = -1;
	temp = ft_calloc(ft_strlen(str) + 3, sizeof(char));
	if (!temp)
		return (NULL);
	temp[++i] = '`';
	while (str[++j])
		temp[i + j + 1] = str[j];
	temp[i + j + 1] = '\'';
	return (temp);

}

void	ft_error(int error, char *arg)
{
	if (error == 1)
		ft_putendl_fd(NEWLINE_ERR, 2);
	else if (error == 2)
		ft_putendl_fd(SYNTAX_ERR, 2);
	else if (error == 3)
		ft_putendl_fd(NO_FILE_ERR, 2);
	else if (error == 4)
		ft_putendl_fd(CMD_NOT_FOUND, 2);
	else if (error == 5)
		ft_putendl_fd(PERM_ERR, 2);
	else if (error == 6)
		ft_putendl_fd(ft_strjoin(SYNTAX_ERR, add_quotes(arg)), 2);
}

void	ft_error1(int error, char *arg, int exit_code, char *message)
{
	if (error == 1)
		ft_putendl_fd(NEWLINE_ERR, 2);
	else if (error == 2)
		ft_putendl_fd(SYNTAX_ERR, 2);
	else if (error == 3)
	{
		ft_putendl_fd(NO_FILE_ERR, 2);
		g_mini->exit_status = exit_code;
	}
	else if (error == 4)
	{
		ft_putstr_fd(message, 2);
		ft_putendl_fd(CMD_NOT_FOUND, 2);
		g_mini->exit_status = exit_code;
	}
	else if (error == 5)
		ft_putendl_fd(PERM_ERR, 2);
	else if (error == 6)
		ft_putendl_fd(ft_strjoin(SYNTAX_ERR, add_quotes(arg)), 2);
	else if (error == 7)
	{
		ft_putstr_fd("minishell> exit: ", STDERR_FILENO);
		ft_putendl_fd(NUM_REQ, 2);
		g_mini->exit_status = exit_code;
	}
	else if (error == 8)
	{
		ft_putstr_fd("minishell> exit: ", STDERR_FILENO);
		ft_putendl_fd(message, 2);
		g_mini->exit_status = exit_code;
	}
	else if (error == 9)
	{
		ft_putstr_fd("minishell> export: ", STDERR_FILENO);
		ft_putendl_fd(ft_strjoin(add_quotes(arg), message), 2);
		g_mini->exit_status = exit_code;
	}
}
