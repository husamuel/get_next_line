/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husamuel <husamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:07:04 by husamuel          #+#    #+#             */
/*   Updated: 2024/11/07 10:04:09 by husamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*init_line(char *stash, int *end_loc)
{
	size_t	len;
	char	*line;

	if (!stash || stash[0] == '\0')
	{
		line = malloc(1);
		if (line)
			line[0] = '\0';
		return (line);
	}
	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, stash, len);
	line[len] = '\0';
	if (line[len - 1] == '\n')
		*end_loc = len - 1;
	return (line);
}

size_t	locate_end(char *line)
{
	size_t	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == '\n' || line[i] == '\0')
			return (i + 1);
		i++;
	}
	return (i);
}

char	*extract_line(char *line, char *stash, int *end_loc, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		read_check;
	size_t	line_size;

	while (*end_loc == -1)
	{
		ft_bzero(buffer, (BUFFER_SIZE + 1));
		read_check = read(fd, buffer, BUFFER_SIZE);
		if (read_check == -1)
		{
			free(line);
			ft_bzero(stash, (BUFFER_SIZE + 1));
			return (NULL);
		}
		line_size = locate_end(buffer);
		ft_strlcpy(&stash[0], &buffer[line_size], (BUFFER_SIZE + 1));
		buffer[line_size] = '\0';
		line = ft_strjoin(line, buffer, end_loc);
		if (read_check == 0)
		{
			ft_bzero(stash, BUFFER_SIZE + 1);
			break ;
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*line;
	int			end_loc;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	end_loc = -1;
	line = init_line(stash, &end_loc);
	if (!line)
		return (NULL);
	ft_strlcpy(&stash[0], &stash[end_loc + 1], BUFFER_SIZE + 1);
	line = extract_line(line, stash, &end_loc, fd);
	if (!line || line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
/*
#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h> 
#include "get_next_line.h"

int main(void)
{
    int     fd; 
    char    *line; 


    fd = open("teste.txt", O_RDONLY);
    if (fd == -1) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }


    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line);
    }


    close(fd);

    return 0;
}
*/
