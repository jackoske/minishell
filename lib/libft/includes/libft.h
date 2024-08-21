/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:37:54 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/21 17:53:18 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				ft_bzero(void *s, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strchr(const char *str, int c);
size_t				ft_strlen(const char *s);
char				ft_tolower(int c);
char				ft_toupper(int c);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s);
char				*ft_substr(const char *s, unsigned int start, size_t len);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strjoin_free(char *s1, char *s2);
char				*ft_strtrim(const char *s1, const char *set);
char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
int					ft_putchar_fd(char c, int fd);
int					ft_putstr_fd(const char *str, int fd);
int					ft_putendl_fd(const char *str, int fd);
int					ft_putnbr_fd(int n, int fd);
char				**ft_split(const char *s, char c);
char				*ft_itoa(int n);
void				*ft_realloc(void *ptr, size_t size);
int					ft_is_special_in_str(char *str);

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

int					ft_2d_array_len(char **array);
char				*ft_quote_string(const char *str);
int					ft_print_2d_array_fd(char **array, int fd);
void				ft_free_2d_array(char ***array);
void				ft_copy_2d_array_i(char ***dest, char **src, int index);
char				**ft_duplicate_2d_array(char **array);
char				**ft_add_row_2d_array(char **array, char *row,
						int free_row);
char				**ft_add_row_2d_array_i(char ***out, char *row, int i);
char				**ft_splice_2d_array(char **dest, char **src, int i);
char				**ft_realloc_2d_array(char **array, int new_size);
int					ft_count_char(const char *str, char c);
int					ft_1st_char_in_set_i(const char *str, const char *set);
int					ft_is_space(char c);
int					ft_strchr_i(const char *s, int c);
int					ft_is_only_special(char *str);
int					ft_is_special_symbol(char c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_isstr_digit(char *str);
char				*ft_remove_paired_quotes(char *str);
int					ft_is_quote(char c);
int					ft_is_string_quoted(const char *str);
int					ft_contains_special_symbols(const char *str);

#endif
