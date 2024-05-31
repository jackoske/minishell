/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:09:11 by Jskehan           #+#    #+#             */
/*   Updated: 2024/05/31 17:58:33 by iverniho         ###   ########.fr       */
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

int ft_print_2d_array_fd(char **array, int fd)
{
	int i;

	i = 0;
	while (array && array[i])
	{
		ft_putendl_fd(array[i], fd);
		i++;
	}
	return (i);
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

void	ft_free_2d_array(char ***array)
{
	int	i;

	i = 0;
	while (array && *array && (*array)[i])
	{
		free((*array)[i]);
		i++;
	}
	if (array && (*array))
	{
		free(*array);
		*array = NULL;
	}
}

int	ft_2d_array_len(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		i++;
	return (i);
}

char	**ft_duplicate_2d_array(char **array)
{
	char	**dup;
	int		i;

	i = 0;
	dup = (char **)malloc(sizeof(char *) * (ft_2d_array_len(array)));
	if (!dup)
		return (NULL);

	while (array && array[i])
	{
		dup[i] = ft_strdup(array[i]);
		if (!dup[i])
			return (ft_free_2d_array(&dup), NULL);
		i++;
	}
	dup[i] = 0;
	return (dup);
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

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(size);
	if (new_ptr != NULL)
	{
		if (size < sizeof(ptr))
			copy_size = size;
		else
			copy_size = sizeof(ptr);
		ft_memcpy(new_ptr, ptr, copy_size);
		free(ptr);
	}
	return (new_ptr);
}

char	*replace_var(char *var, char *value)
{
	ft_realloc(var, ft_strlen(value));
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


	buff = malloc(sizeof(char) * ft_strlen(var));
	out = malloc(sizeof(char *) * ft_2d_array_len(splitted));
	j = 0;
	i = 0;
	while (var[i++])
	{
		buff[j] = var[i];
		j++;
	}
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

char	**ft_new_2d_array(int len)
{
	char	**out;

	out = malloc(sizeof(char *) * len);
	if (!out)
		return (NULL);
	return (out);
}

char	**expand_vars(char **splitted, int len, t_command **command)
{
	char	**buff = NULL;
	char	**last_str = NULL;
	int		i;

	i = -1;
	buff = ft_new_2d_array(len + 1);
	buff = ft_duplicate_2d_array(splitted);
	i = -1;
	while (buff[++i])
	{

		if (ft_strchr(buff[i], '$') != NULL)
		{
			last_str = find_env_var_and_replace(splitted[i], command, splitted);
		}
	}
	if (!last_str)
		return (splitted);
	return (last_str);
}
/*splits by spaces, taking quotted elements into consideration*/
char	**split_into_tokens(char *input, t_command **command)
{
	char	**splitted;
	char	**out;
	char	*buff;

	out = NULL;
	splitted = NULL;
	buff = ft_strtrim(input, " ");
	splitted = split_by_spaces(input, calc_w_count(buff));
	out = malloc(sizeof(char *) * calc_w_count(buff));
	out = expand_vars(splitted, calc_w_count(buff), command);
	return (out);
}

void	prompt_loop(t_command **command)
{
	char	*input;
	char	**splitted;
	// int i = 0;

	while (1)
	{
		print_prompt();

		input = read_command();
		splitted = split_into_tokens(input, command);
		// while (splitted[i])
		// {
		// 	printf("splitted very last step: %s\n", splitted[i]);
		// 	i++;
		// }
		if (input == NULL)
		{
			break ;
		}
		free(input);
	}
}
