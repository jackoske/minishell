/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:31:00 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/21 17:31:18 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to calculate the new length after replacements
int	calculate_new_length(const char *input, int replacement_len)
{
	int	input_len;
	int	new_len;
	int	i;

	input_len = ((new_len = 0), (i = 0), ft_strlen(input));
	while (i < input_len)
	{
		if (input[i] == '?' || (input[i] == '$' && i + 1 < input_len && input[i \
				+ 1] == '?'))
		{
			new_len += replacement_len;
			if (input[i] == '$')
				i += 2;
			else
				i += 1;
		}
		else
		{
			new_len += 1;
			i++;
		}
	}
	return (new_len);
}

// Function to replace special signs and build the new string
void	replace_and_build(const char *input, char *output,
		const char *replacement_value)
{
	int	input_len;
	int	replacement_len;
	int	i;
	int	j;
	int	k;

	input_len = ((i = 0), (j = 0), strlen(input));
	replacement_len = strlen(replacement_value);
	while (i < input_len)
	{
		if (input[i] == '?' || (input[i] == '$' && i + 1 < input_len && input[i \
				+ 1] == '?'))
		{
			k = 0;
			while (k < replacement_len)
				output[j++] = replacement_value[k++];
			if (input[i] == '$')
				i += 2;
			else
				i++;
		}
		else
			output[j++] = input[i++];
	}
	output[j] = '\0';
}

// Main function that orchestrates the replacement process
char	*replace_special_signs(const char *input)
{
	char	*replacement_value;
	int		replacement_len;
	int		new_len;
	char	*output;

	replacement_value = ft_itoa(g_mini->exit_status);
	replacement_len = strlen(replacement_value);
	new_len = calculate_new_length(input, replacement_len);
	output = NULL;
	output = (char *)malloc(new_len + 1);
	if (!output)
	{
		free(replacement_value);
		return (NULL);
	}
	replace_and_build(input, output, replacement_value);
	free(replacement_value);
	return (output);
}

int	is_str_has_sigle_quottes(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			quote++;
		i++;
	}
	if (quote % 2 == 0)
		return (1);
	return (0);
}

int	has_single_quoting(const char *str)
{
	size_t	len;

	len = strlen(str);
	if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
		return (1);
	return (0);
}
