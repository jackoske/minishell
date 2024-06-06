/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:09:11 by Jskehan           #+#    #+#             */
/*   Updated: 2024/06/06 12:29:07 by Jskehan          ###   ########.fr       */
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

int	ft_word_count(char *input)
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

void	populateTokenArray(char **tokenizedInput, char *input)
{
	int	j;
	int	k;
	int	quote[2];
	int	begin;
	int	end;

	quote[0] = ((j = 0), (quote[1] = 0), (begin = 0), (end = 0), (k = 0), 0);
	while (input[end])
	{
		while (ft_strchr(" ", input[end]) && input[end] != '\0')
			end++;
		begin = end;
		while ((!ft_strchr(" ", input[end]) || quote[0] || quote[1])
			&& input[end])
		{
			quote[0] = (quote[0] + (!quote[1] && input[end] == '\'')) % 2;
			quote[1] = (quote[1] + (!quote[0] && input[end] == '\"')) % 2;
			end++;
		}
		if (begin >= (int)ft_strlen(input))
			tokenizedInput[k++] = "\0";
		else
			tokenizedInput[k++] = ft_substr(input, begin, end - begin);
	}
}

char	**split_by_spaces(char *input, int w_count)
{
	char	**tokenizedInput;

	tokenizedInput = malloc(sizeof(char *) * w_count + 1);
	if (!tokenizedInput)
		return (NULL);
	populateTokenArray(tokenizedInput, input);
	return (tokenizedInput);
}

char	*find_var(char *var, t_mini **mini)
{
	int		i;
	char	*value;

	i = -1;
	value = NULL;
	while ((*mini)->envp[++i])
	{
		if (ft_strncmp((*mini)->envp[i], var, ft_strlen(var)) == 0)
		{
			value = ft_strdup((*mini)->envp[i] + ft_strlen(var) + 1);
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
char	**find_env_var_and_replace(char *var, t_mini **mini,
		char **tokenizedInput)
{
	char	*tempTokenArray;
	int		i;
	int		j;
	char	**expandedArray;

	expandedArray = NULL;
	tempTokenArray = ft_calloc(ft_strlen(var) + 1, sizeof(char));
	expandedArray = ft_calloc(ft_2d_array_len(tokenizedInput) + 1,
			sizeof(char *));
	j = 0;
	i = 0;
	while (var[i++])
		tempTokenArray[j++] = var[i];
	tempTokenArray[j] = '\0';
	i = -1;
	while (tokenizedInput[++i])
	{
		if (ft_strchr(tokenizedInput[i], '$') == NULL)
			expandedArray[i] = ft_strdup(tokenizedInput[i]);
		else
			expandedArray[i] = ft_strdup(replace_var(var,
						find_var(tempTokenArray, mini)));
	}
	return (expandedArray);
}

char	**expand_vars(char **tokenizedInput, t_mini **mini)
{
	char	**tempTokenArray;
	char	**last_str;
	int		i;

	tempTokenArray = NULL;
	last_str = NULL;
	i = -1;
	if (!ft_splice_2d_array(&tempTokenArray, tokenizedInput, 0))
		return (NULL);
	printf("tempTokenArray:\n");
	ft_print_2d_array_fd(tempTokenArray, 1);
	while (tempTokenArray[++i])
	{
		if (ft_strchr(tempTokenArray[i], '$') != NULL)
			last_str = find_env_var_and_replace(tokenizedInput[i], mini,
					tokenizedInput);
	}
	if (!last_str)
		return (tokenizedInput);
	printf("last_str:\n");
	ft_print_2d_array_fd(last_str, 1);
	return (last_str);
}

int	is_special_symbol(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

// int	ft_is_space(char c)
// {
// 	return (c == ' ' || (c >= '\t' && c <= '\r'));
// }

/*Function to separate a string into tokens based on special symbols*/
char	**tokenize_special_symbols(const char *str)
{
	char	**tokens;
	int		token_count;
	int		i;
	int		len;
	int		symbol_len;
	int		start;
	int		word_len;

	token_count = 0;
	tokens = ft_calloc(100, sizeof(char *));
	if (!tokens)
		return (NULL);
	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (ft_is_space(str[i]))
		{
			i++;
			continue ;
		}
		if (is_special_symbol(str[i]))
		{
			symbol_len = 1;
			if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i
					+ 1] == '>'))
				symbol_len = 2;
			tokens[token_count] = malloc((symbol_len + 1) * sizeof(char));
			ft_strlcpy(tokens[token_count], &str[i], symbol_len + 1);
			tokens[token_count][symbol_len] = '\0';
			token_count++;
			i += symbol_len;
		}
		else
		{
			start = i;
			while (i < len && !ft_is_space(str[i])
				&& !is_special_symbol(str[i]))
				i++;
			word_len = i - start;
			tokens[token_count] = malloc((word_len + 1) * sizeof(char));
			ft_strlcpy(tokens[token_count], &str[start], word_len + 1);
			tokens[token_count][word_len] = '\0';
			token_count++;
		}
	}
	tokens[token_count] = NULL;
	return (tokens);
}

/*splits by spaces, taking quotted elements into consideration*/
char	**tokenize_input(char *input, t_mini **mini)
{
	char	**tokenizedInput;
	char	**expandedArray;
	char	**tempTokenArray;
	char	**specialSymbolArray;
	int		i;
	int		j;
	int		k;

	j = ((i = -1), (k = -1), (expandedArray = NULL), (tokenizedInput = NULL),
			-1);
	tokenizedInput = split_by_spaces(input, ft_word_count(ft_strtrim(input,
					" ")));
	printf("tokenizedInput: %d\n", ft_2d_array_len(tokenizedInput));
	ft_print_2d_array_fd(tokenizedInput, 1);
	expandedArray = ft_calloc(ft_word_count(ft_strtrim(input, " ")) + 1,
			sizeof(char *));
	expandedArray = expand_vars(tokenizedInput, mini);
	printf("expandedArray:\n");
	// ft_print_2d_array_fd(expandedArray, 1);
	specialSymbolArray = ft_calloc(100, sizeof(char *));
	tempTokenArray = ft_calloc(100, sizeof(char *));
	// while (expandedArray[++i])
	// {
	// 	if (ft_1st_char_in_set_i(expandedArray[i], "<>|"))
	// 	{
	// 		specialSymbolArray = tokenize_special_symbols(expandedArray[i]);
	// 		j = -1;
	// 		while (specialSymbolArray[++j])
	// 		{
	// 			tempTokenArray[++k] = ft_strdup(specialSymbolArray[j]);
	// 			i++;
	// 		}
	// 		i -= 2;
	// 		ft_free_2d_array(&specialSymbolArray);
	// 	}
	// 	else
	// 		tempTokenArray[++k] = ft_strdup(expandedArray[i]);
	// }
	return (tempTokenArray);
}

void	prompt_loop(t_mini *mini)
{
	char	*input;
	char	**tokenizedInput;
	int		i;

	tokenizedInput = NULL;
	while (1)
	{
		print_prompt();
		input = read_command();
		if (input == NULL || input[0] == '\0')
		{
			free(input);
			continue ;
		}
		tokenizedInput = tokenize_input(input, &mini);
		i = -1;
		while (tokenizedInput && tokenizedInput[++i])
			printf("tokenizedInput very last step: %s\n", tokenizedInput[i]);
		free(input);
	}
}
