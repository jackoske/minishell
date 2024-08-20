/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:46:05 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/20 16:18:44 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

static int	count_tokens(const char *str)
{
	int		count;
	int		in_quote;
	char	quote_char;

	count = 0;
	in_quote = 0;
	quote_char = '\0';
	while (*str)
	{
		while (*str && is_space(*str))
			str++;
		if (*str)
			count++;
		while (*str && (!is_space(*str) || in_quote))
		{
			if (is_quote(*str))
			{
				if (in_quote && *str == quote_char)
					in_quote = 0;
				else if (!in_quote)
				{
					in_quote = 1;
					quote_char = *str;
				}
			}
			str++;
		}
	}
	return (count);
}

static char	*get_next_token(const char **str)
{
	const char	*start;
	char		*token;
	int			in_single_quote;
	int			in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	while (**str && is_space(**str))
		(*str)++;
	start = *str;
	while (**str && (!is_space(**str) || in_single_quote || in_double_quote))
	{
		if (**str == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (**str == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		(*str)++;
	}
	token = strndup(start, *str - start);
	return (token);
}

char	**tokenize_sp_symb(const char *str, int i, int token_count)
{
	char	**tokens;
	int		start;
	int		len;

	tokens = malloc(100 * sizeof(char *));
	if (!tokens)
		return (NULL);
	while (str[i] && token_count < 100)
	{
		if (ft_is_special_symbol(str[i]))
		{
			len = 1;
			if ((str[i] == '>' || str[i] == '<') && str[i + 1] == str[i])
				len++;
			tokens[token_count++] = ft_substr(str, i, len);
			i += len;
		}
		else
		{
			start = i;
			while (str[i] && !ft_is_special_symbol(str[i]))
				i++;
			tokens[token_count++] = ft_substr(str, start, i - start);
		}
	}
	tokens[token_count] = NULL;
	return (tokens);
}

static char	**process_special_symbols(char *token, char **tmpTokArr)
{
	char	**split_tokens;
	int		i;

	split_tokens = tokenize_sp_symb(token, 0, 0);
	if (!split_tokens)
		return (NULL);
	i = 0;
	while (split_tokens[i])
	{
		tmpTokArr = ft_add_row_2d_array(tmpTokArr, split_tokens[i], 0);
		if (!tmpTokArr)
		{
			ft_free_2d_array(&split_tokens);
			return (NULL);
		}
		i++;
	}
	ft_free_2d_array(&split_tokens);
	return (tmpTokArr);
}

int	contains_special_symbols(const char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '<' || *str == '>' || *str == '|')
			return (1);
		str++;
	}
	return (0);
}

int	is_string_quoted(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '\"' && str[len
			- 1] == '\"'))
		return (1);
	return (0);
}

static char	**process_expanded_array(char **expandedArray, char **tmpTokArr)
{
	int	i;

	i = 0;
	while (expandedArray[i])
	{
		if (is_string_quoted(expandedArray[i]))
			tmpTokArr = ft_add_row_2d_array(tmpTokArr,
					ft_remove_paired_quotes(expandedArray[i]), 0);
		else if (contains_special_symbols(expandedArray[i]))
		{
			tmpTokArr = process_special_symbols(expandedArray[i], tmpTokArr);
			if (!tmpTokArr)
				return (NULL);
		}
		else
			tmpTokArr = ft_add_row_2d_array(tmpTokArr, expandedArray[i], 0);
		if (!tmpTokArr)
		{
			printf("Error processing token: %s\n", expandedArray[i]);
			return (NULL);
		}
		i++;
	}
	return (tmpTokArr);
}

static t_cmd	*initialize_command(void)
{
	t_cmd	*cmd;

	cmd = init_cmd();
	if (!cmd)
		return (NULL);
	cmd->full_command = ft_calloc(1, sizeof(char *));
	if (!cmd->full_command)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

static int	validate_command(t_cmd *cmd)
{
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
	{
		free_cmd(cmd);
		return (0);
	}
	return (1);
}

static char	**process_command(t_cmd *cmd, char **tokenized_input)
{
	char	**new_array;

	new_array = ft_add_row_2d_array(cmd->full_command, *tokenized_input, 0);
	if (!new_array)
	{
		free_cmd(cmd);
		return (NULL);
	}
	cmd->full_command = new_array;
	return (tokenized_input + 1);
}

static char	**process_token(t_cmd *cmd, char **tokenized_input,
		int *error_status)
{
	if (is_redirection(*tokenized_input))
	{
		*error_status = process_redirections(cmd, &tokenized_input);
		if (*error_status)
			return (NULL);	
		return (tokenized_input);
	}
	else
		return (process_command(cmd, tokenized_input));
}

t_cmd	*create_command_node(char **tokenized_input)
{
	t_cmd	*cmd;
	int		error_status;

	error_status = 0;
	cmd = initialize_command();
	if (!cmd)
		return (NULL);
	while (*tokenized_input && **tokenized_input != '|')
	{
		tokenized_input = process_token(cmd, tokenized_input, &error_status);
		if (error_status)
		{
			free_cmd(cmd);
			return (NULL);
		}
		if (!tokenized_input)
			return (NULL);
	}
	if (!validate_command(cmd))
		return (NULL);
	return (cmd);
}

t_list	*create_commands(char **tokenized_input)
{
	t_list	*commands;
	t_cmd	*cmd;

	commands = NULL;
	while (*tokenized_input)
	{
		cmd = create_command_node(tokenized_input);
		if (!cmd)
		{
			while (*tokenized_input && **tokenized_input != '|')
				tokenized_input++;
			if (*tokenized_input)
				tokenized_input++;
			continue ;
		}
		ft_lstadd_back(&commands, ft_lstnew(cmd));
		while (*tokenized_input && **tokenized_input != '|')
			tokenized_input++;
		if (*tokenized_input)
			tokenized_input++;
	}
	return (commands);
}
char	**split_spaces(const char *str, int token_count)
{
	char	**tokens;
	int		i;

	if (!str)
		return (NULL);
	token_count = count_tokens(str);
	tokens = (char **)malloc((token_count + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	i = 0;
	while (i < token_count)
	{
		tokens[i] = get_next_token(&str);
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}

char	**tokenize_input(char *input)
{
	char	**tok_input;
	char	**expanded_arr;
	char	**final_tokens;

	tok_input = split_spaces(input, w_count_quotes(input));
	if (!tok_input)
		return (NULL);
	expanded_arr = expand_vars(tok_input);
	if (!expanded_arr)
	{
		ft_free_2d_array(&tok_input);
		return (NULL);
	}
	final_tokens = process_expanded_array(expanded_arr, NULL);
	ft_free_2d_array(&expanded_arr);
	ft_free_2d_array(&tok_input);
	if (!final_tokens)
		return (NULL);
	return (ft_add_row_2d_array(final_tokens, NULL, 1));
}
