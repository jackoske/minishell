/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:09:11 by Jskehan           #+#    #+#             */
/*   Updated: 2024/05/27 10:23:59 by iverniho         ###   ########.fr       */
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
		printf("Command entered: %s\n", input);
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

// void	create_first_el(t_token **token, t_token **head, char *buff, char *input)
// {
// 	*token = ft_lstnew1(buff, input);
// 	(*token)->head = *token;
// 	head = token;
// 	printf("Token1: %s\n", (*token)->content);
// 	printf("test1\n");
// }

// void	create_second_el(t_token *token, t_token *head, char *buff, char *input)
// {
// 	printf("test2\n");
// 	token = ft_lstnew1(buff, input);
// 	printf("test3\n");
// 	printf("Token2: %s\n", token->content);
// 	printf("head: %s\n", head->content);
// 	head->next = token;
// 	printf("test4\n");
// 	token->head = head;
// 	printf("test5\n");
// }

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
	else if (ft_strncmp(token->content, "\"", 1) == 0)
		token->type = quote;
	else if (ft_strncmp(token->content, "'", 1) == 0)
		token->type = quote;
	else if (is_builtin(token) == 0)
		token->type = builtin;
	else
		token->type = command;
}

t_token	*split_into_tokens(char *input)
{
	t_token	*token;
	t_token	*tmp;
	char	**buff;
	int		i;
	t_token	*head;

	token = (buff = ft_split(input, ' '), head = NULL, i = -1,NULL);
	while (buff[++i])
	{
		if (i == 0)
			// create_first_el(token, head, buff[i], input);
		{
			token = ft_lstnew1(buff[i], input);
			token->head = token;
			add_type(token);
			head = token;
		}
		else if (i == 1)
			// create_second_el(token, head, buff[i], input);
		{
			printf("Token2: %s\n", token->content);
			token = ft_lstnew1(buff[i], input);
			head->next = token;
			token->head = head;
			add_type(token);
		}
		else
		{
			tmp = ft_lstnew1(buff[i], input);
			token->next = tmp;
			token->head = head;
			token = tmp;
			add_type(token);
			// printf("Token2 %d: %s\n", i, token->content);
		}
	}
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
