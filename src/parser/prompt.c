/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:09:11 by Jskehan           #+#    #+#             */
/*   Updated: 2024/05/23 17:14:57 by iverniho         ###   ########.fr       */
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

t_token	*ft_lstnew1(void *content)
{
	t_token	*item;

	item = malloc(sizeof(t_token));
	if (!item)
		return (NULL);
	item->content = content;
	item->next = NULL;
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

t_token	**split_into_tokens(char *input)
{
	t_token	*token;
	t_token	**tokens;
	char	**buff;
	int		i;
	int		j;

	token = NULL;
	tokens = NULL;
	buff = ft_split(input, ' ');
	i = -1;
	j = -1;
	// while (is_special_character(input[++j]))
	// 	if (input[j] == ' ')
	// 		printf("Space detected\n");
	while (buff[++i])
		{
			printf("buff[%d]: %s\n", i, buff[i]);
			if (i == 0)
			{
				token = ft_lstnew1(buff[i]);
				tokens = &token;
				printf("Token1 %d: %s\n", i, token->content);
			}
			else
			{
				token->next = ft_lstnew1(buff[i]);
				ft_lstadd_back1(tokens, token);
				printf("Token2 %d: %s\n", i, token->content);
			}
		}
	return (tokens);
}

void	prompt_loop(void)
{
	char	*input;
	t_token	**tokens = NULL;

	while (1)
	{
		print_prompt();
		input = read_command();
		tokens = split_into_tokens(input);
		printf("Token 0: %s\n", (*tokens)->content);
		if (input == NULL)
		{
			break ;
		}
		free(input);
	}
}
