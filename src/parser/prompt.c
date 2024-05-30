/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:09:11 by Jskehan           #+#    #+#             */
/*   Updated: 2024/05/31 00:10:07 by Jskehan          ###   ########.fr       */
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

t_token	*ft_lstnew1(void *content, char *input)
{
	t_token	*item;

	item = malloc(sizeof(t_token));
	if (!item)
		return (NULL);
	item->content = content;
	item->next = NULL;
	item->cmd = input;
	return (item);
}

void	ft_lstadd_back1(t_token **alst, t_token *new)
{
	t_token	*elem;

	if (alst == NULL || new == NULL)
		return ;
	if (*alst == NULL)
		*alst = new;
	else
	{
		elem = *alst;
		while (elem->next != NULL)
			elem = elem->next;
		elem->next = new;
	}
}

int	is_special_character(char c)
{
	if (c == '$' || c == '|' || c == '>' || c == '<' \
		|| c == '?' || c == '(' || c == ')')
		return (1);
	return (0);
}



int	is_builtin(t_token *token)
{
	if (ft_strncmp(token->content, "echo", 4) == 0)
		return(token->type = builtin, 0);
	else if (ft_strncmp(token->content, "cd", 2) == 0)
		return(token->type = builtin, 0);
	else if (ft_strncmp(token->content, "pwd", 3) == 0)
		return(token->type = builtin, 0);
	else if (ft_strncmp(token->content, "export", 6) == 0)
		return(token->type = builtin, 0);
	else if (ft_strncmp(token->content, "unset", 5) == 0)
		return(token->type = builtin, 0);
	else if (ft_strncmp(token->content, "env", 3) == 0)
		return(token->type = builtin, 0);
	else if (ft_strncmp(token->content, "exit", 4) == 0)
		return(token->type = builtin, 0);
	else
		return (1);
}

void	add_type(t_token *token)
{
	if (ft_strncmp(token->content, ">", 1) == 0)
		token->type = red_out;
	else if (ft_strncmp(token->content, ">>", 2) == 0)
		token->type = append;
	else if (ft_strncmp(token->content, "<", 1) == 0)
		token->type = red_in;
	else if (ft_strncmp(token->content, "|", 1) == 0)
		token->type = pipe_symb;
	else if (ft_strncmp(token->content, ">", 1) == 0)
		token->type = red_out;
	else if (ft_strncmp(token->content, ">>", 2) == 0)
		token->type = append;
	else if (ft_strncmp(token->content, "<", 1) == 0)
		token->type = red_in;
	else if (ft_strncmp(token->content, "\"", 1) == 0 || \
		ft_strncmp(token->content, "\'", 1) == 0)
		token->type = quote;
	else if (is_builtin(token) == 0)
		token->type = builtin;
	else
		token->type = command;
}

static void	create_first_el(t_token **token, t_token **head, char *buff, char *input)
{
	(*token) = ft_lstnew1(buff, input);
	(*token)->head = *token;
	(*head) = *token;
	add_type(*token);
}

static void	create_second_el(t_token **token, t_token **head, char *buff, char *input)
{
	(*token) = ft_lstnew1(buff, input);
	(*head)->next = *token;
	(*token)->head = *head;
	add_type(*token);
}

static void create_next_el(t_token **token, t_token **head, char *buff, char *input)
{
	t_token	*tmp;

	tmp = ft_lstnew1(buff, input);
	(*token)->next = tmp;
	(*token)->head = *head;
	(*token) = tmp;
	add_type((*token));
}

void	init_token(t_token **token, t_token **head, char *input)
{
	int		i;
	char	**buff;

	buff = ft_split(input, ' ');
	i = -1;
	while (buff[++i])
	{
		if (i == 0)
			create_first_el(token, head, buff[i], input);
		else if (i == 1)
			create_second_el(token, head, buff[i], input);
		else
			create_next_el(token, head, buff[i], input);
	}
}

t_token	*split_into_tokens(char *input)
{
	t_token	*token;
	int		i;
	t_token	*head;

	token = ( head = zNULL, i = -1,NULL);
	init_token(&token, &head, input);
	return (head);
}

void	prompt_loop(void)
{
	char	*input;
	t_token	*token;

	while (1)
	{
		print_prompt();
		input = read_command();
		token = split_into_tokens(input);
		t_token	*current_token = token->head;
		while (current_token)
		{
			printf("Token3: %s\n", current_token->content);
			printf("Type: %d\n", current_token->type);
			current_token = current_token->next;
		}
		if (input == NULL)
		{
			break ;
		}
		free(input);
	}
}
