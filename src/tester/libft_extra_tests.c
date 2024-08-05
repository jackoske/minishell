/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extra_tests.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:00:46 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/05 15:08:46 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void libft_extra_tester(void)
{
	printf("This is a test\n");
	char **env = ft_split("PATH=/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", ':');
	char **path = ft_split("PATH=dasdas=dsdassas=sedsa=as=dsad=sd=as", '=');
	char **empty = NULL;
	printf("\nTEST1\n");
	ft_print_2d_array_fd(env, 1);
	printf("\nTEST2\n");
	ft_print_2d_array_fd(path, 1);

	printf("\nTEST3\n");
	empty = ft_splice_2d_array(empty, env, 0);
	env = ft_splice_2d_array(env, path, 0);
	env = ft_splice_2d_array(env, path, 0);

	printf("\n%d\n", ft_2d_array_len(env));
	
	env = ft_add_row_2d_array(env, "PATH=/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", 0);
	env = ft_add_row_2d_array(env, "PATH=/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", 0);
	ft_print_2d_array_fd(env, 1);
	printf("\n%d\n", ft_2d_array_len(env));

	printf("\nTEST4\n");
	printf("\nempty_len:%d\n", ft_2d_array_len(empty));
	empty = ft_add_row_2d_array(empty, "PATH=/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", 0);
	ft_print_2d_array_fd(empty, 1);


	printf("\nTEST5\n");
	char **tmp = ft_duplicate_2d_array(empty);
	ft_print_2d_array_fd(tmp, 1);


	printf("\nTEST6\n");
	printf("\n%d\n", ft_count_char("hellodsdadaa dkkdskdsa sdda ", 'a'));
	printf("\n%d\n", ft_count_char("hellodsdadaa dkkdskdsa sdda ", ' '));

	printf("\nTEST7\n");
	char **tmp2 = ft_split("1:2:3:4:5:6", ':');
	printf("\nshould be 6 \n");
	printf("\n2darraylen: %d\n", ft_2d_array_len(tmp2));

	printf("\nTEST8\n");
	printf("\n%d\n", ft_1st_char_in_set_i("hellodsdadaa dkkdskdsa sdda ", "ael"));

	printf("\nTEST9\n");
	printf("\n%d\n", ft_strchr_i("hellodsdadaa dkkdskdsa sdda ", 'a'));

	printf("\nTEST10\n");
	printf("\nhere before realloc size:%d\n", ft_2d_array_len(env));
	env = ft_realloc_2d_array(env, 20);
	printf("\nhere:%d\n", ft_2d_array_len(env));
	ft_print_2d_array_fd(env, 1);


	printf("\nTEST11\n");
	char **empty2 = NULL;
	empty2 = ft_splice_2d_array(empty2, env, 0);
	ft_print_2d_array_fd(empty2, 1);
	
	printf("\nTEST12\n");
	char **empty3 = NULL;
	empty3 = ft_add_row_2d_array(empty3, "PATH=/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", 0);
	empty3 = ft_add_row_2d_array(empty3, "PATH=/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", 0);
	empty3 = ft_add_row_2d_array(empty3, "PATH=/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", 0);
	empty3 = ft_add_row_2d_array(empty3, "PATH=/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", 0);
	ft_print_2d_array_fd(empty3, 1);
	
	ft_free_2d_array(&empty3);
	ft_free_2d_array(&empty2);
	ft_free_2d_array(&env);
	ft_free_2d_array(&path);
	ft_free_2d_array(&empty);
	ft_free_2d_array(&tmp);
}
