/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:19:32 by Jskehan           #+#    #+#             */
/*   Updated: 2024/01/11 22:07:28 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

static int	ft_readline(char **buffer, int fd)
{
	char	*read_buff;
	int		ret;
	int		end_of_line_found;

	read_buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!read_buff)
		return (-1);
	ret = 1;
	end_of_line_found = 0;
	while (ret > 0 && !end_of_line_found)
	{
		ret = read(fd, read_buff, BUFFER_SIZE);
		if (ret <= 0)
			break ;
		read_buff[ret] = '\0';
		if (ft_strchr(read_buff, '\n'))
			end_of_line_found = 1;
		*buffer = ft_strjoin_free(*buffer, read_buff);
		if (!*buffer)
			break ;
	}
	free(read_buff);
	if (ret <= -1)
		return (-1);
	return (end_of_line_found);
}

void	create_line_and_update_buffer(char **buffer, char **line)
{
	int		length;
	char	*temp;

	temp = ft_strchr(*buffer, '\n');
	if (temp)
		length = temp - *buffer + 1;
	else
		length = ft_strlen(*buffer);
	*line = ft_substr(*buffer, 0, length);
	if (!*line)
	{
		free(*buffer);
		return ;
	}
	temp = *buffer;
	*buffer = ft_substr(*buffer, length, ft_strlen(*buffer));
	free(temp);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;
	int			read_status;

	line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 1024)
		return (NULL);
	if (buffer == NULL)
		buffer = ft_strdup("");
	read_status = ft_readline(&buffer, fd);
	if (!buffer || buffer == NULL || buffer[0] == '\0' || read_status == -1)
	{
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}
		if (line)
			free(line);
		return (NULL);
	}
	create_line_and_update_buffer(&buffer, &line);
	return (line);
}
