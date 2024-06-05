/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:09:11 by Jskehan           #+#    #+#             */
/*   Updated: 2024/06/05 19:52:36 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_prompt(void)
{
	printf("%s", PROMPT);
	rl_on_new_line();
}

static int	check_command(char *input)
{
	if (!quotes_closed(input))
		return (printf("Syntax error\n"), 0);
	return (1);
}

static char	*read_command(void)
{
	char	*input;

	input = readline("");
	if (input != NULL && check_command(input))
	{
		add_history(input);
	}
	return (input);
}

int	calc_w_count(char *input)
{
	int		i;
	int		count;
	char	quote;

	quote = ((i = 0), (count = 0), 0);
	while (input[i])
	{
		if (input[i] == ' ')
		{
			while (input[i] == ' ')
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

void	set_array(char **splitted, char *input)
{
	int		j;
	int		k;
	int		quote[2];
	int		begin;
	int		end;

	quote[0] = ((j = 0), (quote[1] = 0), (begin = 0), (end = 0), (k = 0), 0);
	while (input[end])
	{
		while (ft_strchr(" ", input[end]) && input[end] != '\0')
			end++;
		begin = end;
		while ((!ft_strchr(" ", input[end]) || quote[0] || quote[1]) && input[end])
		{
			quote[0] = (quote[0] + (!quote[1] && input[end] == '\'')) % 2;
			quote[1] = (quote[1] + (!quote[0] && input[end] == '\"')) % 2;
			end++;
		}
		if (begin >= (int)ft_strlen(input))
			splitted[k++] = "\0";
		else
			splitted[k++] = ft_substr(input, begin, end - begin);
	}
}

char	**split_by_spaces(char *input, int w_count)
{
	char	**splitted;

	splitted = malloc(sizeof(char *) * w_count + 1);
	if (!splitted)
		return (NULL);
	set_array(splitted, input);
	return (splitted);
}

char	*find_var(char *var, t_command **command)
{
	int		i;
	char	*value;

	i = -1;
	value = NULL;
	while ((*command)->envp[++i])
	{
		if (ft_strncmp((*command)->envp[i], var, ft_strlen(var)) == 0)
		{
			value = ft_strdup((*command)->envp[i] + ft_strlen(var) + 1);
			break ;
		}
	}
	return (value);
}

char	*replace_var(char *var, char *value)
{
	ft_realloc(var, ft_strlen(value) + 1);
	var = ft_strdup(value);
	return (var);
}

// echo "hello      there" how are 'you 'doing? $USER |wc -l >outfile
char	**find_env_var_and_replace(char *var, t_command **command, char **splitted)
{
	char	*buff;
	int		i;
	int		j;
	char **out = NULL;

	buff = ft_calloc(ft_strlen(var) + 1, sizeof(char));
	out = ft_calloc(ft_2d_array_len(splitted) + 1, sizeof(char *));
	j = 0;
	i = 0;
	while (var[i++])
		buff[j++] = var[i];
	buff[j] = '\0';
	i = -1;
	while (splitted[++i])
	{
		if (ft_strchr(splitted[i], '$') == NULL)
			out[i] = ft_strdup(splitted[i]);
		else
			out[i] = ft_strdup(replace_var(var, find_var(buff, command)));
	}
	return (out);
}

char	**expand_vars(char **splitted, t_command **command)
{
	char	**buff = NULL;
	char	**last_str = NULL;
	int		i;

	i = -1;
	if(!ft_splice_2d_array(&buff, splitted, 0))
		return (NULL);
	while (buff[++i])
	{
		if (ft_strchr(buff[i], '$') != NULL)
			last_str = find_env_var_and_replace(splitted[i], command, splitted);
	}
	if (!last_str)
		return (splitted);
	return (last_str);
}

int is_special_symbol(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	ft_is_space(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

/*Function to separate a string into tokens based on special symbols*/
char	**separate_string(const char* str)
{
	char	**tokens;
	int		token_count = 0;
	int		i;

	tokens = ft_calloc(100, sizeof(char*));
	if (!tokens)
		return (NULL);
	i = 0;
	int len = ft_strlen(str);
	while (i < len)
	{
		if (ft_is_space(str[i])) {
			i++;
			continue;
		}
		if (is_special_symbol(str[i]))
		{
			int symbol_len = 1;
			if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
				symbol_len = 2;
			tokens[token_count] = malloc((symbol_len + 1) * sizeof(char));
			ft_strlcpy(tokens[token_count], &str[i], symbol_len + 1);
			tokens[token_count][symbol_len] = '\0';
			token_count++;
			i += symbol_len;
		}
		else
		{
			int start = i;
			while (i < len && !ft_is_space(str[i]) && !is_special_symbol(str[i]))
				i++;
			int word_len = i - start;
			tokens[token_count] = malloc((word_len + 1) * sizeof(char));
			ft_strlcpy(tokens[token_count], &str[start], word_len + 1);
			tokens[token_count][word_len] = '\0';
			token_count++;
		}
	}
	tokens[token_count] = NULL;
	return tokens;
}

/*splits by spaces, taking quotted elements into consideration*/
char	**split_into_tokens(char *input, t_command **command)
{
	char	**splitted;
	char	**out;
	char	**buff;
	char	**buff2;
	int		i;
	int		j;
	int		k;

	j = ((i = -1), (k = -1), (out = NULL), (splitted = NULL), -1);
	splitted = split_by_spaces(input, calc_w_count(ft_strtrim(input, " ")));
	out = ft_calloc(calc_w_count(ft_strtrim(input, " ")) + 1, sizeof(char *));
	out = expand_vars(splitted, command);
	buff2 = ft_calloc(100, sizeof(char *));
	buff = ft_calloc(100, sizeof(char *));
	while (out[++i])
	{
		if (ft_strchr(out[i], '<') || ft_strchr(out[i], '>') || ft_strchr(out[i], '|'))
		{
			buff2 = separate_string(out[i]);
			j = -1;
			while (buff2[++j])
			{
				buff[++k] = ft_strdup(buff2[j]);
				i++;
			}
			i -= 2;
			free(buff2);
		}
		else
			buff[++k] = ft_strdup(out[i]);
	}
	return (buff);
}

void	prompt_loop(t_command **command)
{
	char	*input;
	char	**splitted;

	splitted = NULL;
	while (1)
	{
		print_prompt();
		input = read_command();
		splitted = NULL;
		splitted = split_into_tokens(input, command);
		int i = -1;
		while (splitted[++i])
			printf("splitted very last step: %s\n", splitted[i]);
		if (input == NULL)
			break ;
		free(input);
	}
}
