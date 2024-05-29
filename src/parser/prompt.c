/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:09:11 by Jskehan           #+#    #+#             */
/*   Updated: 2024/05/31 17:55:35 by iverniho         ###   ########.fr       */
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

// t_token	*ft_lstnew1(void *content, char *input)
// {
// 	t_token	*item;

// 	item = malloc(sizeof(t_token));
// 	if (!item)
// 		return (NULL);
// 	item->content = content;
// 	item->next = NULL;
// 	item->cmd = input;
// 	return (item);
// }

// void	ft_lstadd_back1(t_token **alst, t_token *new)
// {
// 	t_token	*elem;

// 	if (alst == NULL || new == NULL)
// 		return ;
// 	if (*alst == NULL)
// 		*alst = new;
// 	else
// 	{
// 		elem = *alst;
// 		while (elem->next != NULL)
// 			elem = elem->next;
// 		elem->next = new;
// 	}
// }

// int	is_special_character(char c)
// {
// 	if (c == '$' || c == '|' || c == '>' || c == '<' \
// 		|| c == '?' || c == '(' || c == ')')
// 		return (1);
// 	return (0);
// }



// int	is_builtin(t_token *token)
// {
// 	if (ft_strncmp(token->content, "echo", 4) == 0)
// 		return(token->type = builtin, 0);
// 	else if (ft_strncmp(token->content, "cd", 2) == 0)
// 		return(token->type = builtin, 0);
// 	else if (ft_strncmp(token->content, "pwd", 3) == 0)
// 		return(token->type = builtin, 0);
// 	else if (ft_strncmp(token->content, "export", 6) == 0)
// 		return(token->type = builtin, 0);
// 	else if (ft_strncmp(token->content, "unset", 5) == 0)
// 		return(token->type = builtin, 0);
// 	else if (ft_strncmp(token->content, "env", 3) == 0)
// 		return(token->type = builtin, 0);
// 	else if (ft_strncmp(token->content, "exit", 4) == 0)
// 		return(token->type = builtin, 0);
// 	else
// 		return (1);
// }

// void	add_type(t_token *token)
// {
// 	if (ft_strncmp(token->content, ">", 1) == 0)
// 		token->type = red_out;
// 	else if (ft_strncmp(token->content, ">>", 2) == 0)
// 		token->type = append;
// 	else if (ft_strncmp(token->content, "<", 1) == 0)
// 		token->type = red_in;
// 	else if (ft_strncmp(token->content, "|", 1) == 0)
// 		token->type = pipe_symb;
// 	else if (ft_strncmp(token->content, ">", 1) == 0)
// 		token->type = red_out;
// 	else if (ft_strncmp(token->content, ">>", 2) == 0)
// 		token->type = append;
// 	else if (ft_strncmp(token->content, "<", 1) == 0)
// 		token->type = red_in;
// 	else if (ft_strncmp(token->content, "\"", 1) == 0 || \
// 		ft_strncmp(token->content, "\'", 1) == 0)
// 		token->type = quote;
// 	else if (is_builtin(token) == 0)
// 		token->type = builtin;
// 	else
// 		token->type = command;
// }

// static void	create_first_el(t_token **token, t_token **head, char *buff, char *input)
// {
// 	(*token) = ft_lstnew1(buff, input);
// 	(*token)->head = *token;
// 	(*head) = *token;
// 	add_type(*token);
// }

// static void	create_second_el(t_token **token, t_token **head, char *buff, char *input)
// {
// 	(*token) = ft_lstnew1(buff, input);
// 	(*head)->next = *token;
// 	(*token)->head = *head;
// 	add_type(*token);
// }

// static void create_next_el(t_token **token, t_token **head, char *buff, char *input)
// {
// 	t_token	*tmp;

// 	tmp = ft_lstnew1(buff, input);
// 	(*token)->next = tmp;
// 	(*token)->head = *head;
// 	(*token) = tmp;
// 	add_type((*token));
// }

// void	init_token(t_token **token, t_token **head, char *input)
// {
// 	int		i;
// 	char	**buff;

// 	buff = ft_split(input, ' ');
// 	i = -1;
// 	while (buff[++i])
// 	{
// 		if (i == 0)
// 			create_first_el(token, head, buff[i], input);
// 		else if (i == 1)
// 			create_second_el(token, head, buff[i], input);
// 		else
// 			create_next_el(token, head, buff[i], input);
// 	}
// }

// t_token	*split_into_tokens(char *input)
// {

// 	t_token	*token;
// 	int		i;
// 	t_token	*head;

// 	token = ( head = NULL, i = -1,NULL);
// 	init_token(&token, &head, input);
// 	return (token);
// }


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

// echo "hello      there" how are 'you 'doing? $USER |wc -l >outfile

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
		// printf("input[end]: %c\n", input[end]);
		// printf("end: %d\n", end);
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
		// printf("splitted: %s\n", splitted[0]);
	}
}




char	**split_by_spaces(char *input, int w_count)
{
	char	**splitted;

	splitted = malloc(sizeof(char *) * w_count + 1);
	if (!splitted)
		return (NULL);
	set_array(splitted, input);
	while (*splitted)
	{
		printf("splitted: %s\n", *splitted);
		splitted++;
	}
	return (splitted);
}
/*splits by spaces, taking quotted elements into consideration*/
char	**split_into_tokens(char *input)
{
	int		i;
	int		j;
	int		k;
	char	**splitted = NULL;
	char	*buff;
	int		w_count;

	i = 0;
	j = 0;
	k = 0;
	buff = ft_strtrim(input, " ");
	w_count = calc_w_count(buff);
	/*change to ft_new_2d_array*/

	splitted = split_by_spaces(input, w_count);
	return (splitted);
}

void	prompt_loop(t_command **command)
{
	char	*input;
	char	**splitted;

	printf("command->envp: %s\n", (*command)->envp[0]);

	while (1)
	{
		print_prompt();

		input = read_command();
		splitted = split_into_tokens(input);
		if (input == NULL)
		{
			break ;
		}
		free(input);
	}
}
