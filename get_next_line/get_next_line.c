/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyasar <yyasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:58:44 by yyasar            #+#    #+#             */
/*   Updated: 2022/12/10 10:19:17 by yyasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*newlinedensonra(char *line)
{
	char	*yeni;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (0);
	}
	yeni = (char *)malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	if (!yeni)
		return (0);
	i++;
	while (line[i])
		yeni[j++] = line[i++];
	yeni[j] = '\0';
	free(line);
	return (yeni);
}

char	*newlinedenonce(char *line)
{
	char	*yeni;
	int		i;

	i = 0;
	if (!line[i])
		return (0);
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	yeni = (char *)malloc(sizeof(char) * (i + 2));
	if (!yeni)
		return (0);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		yeni[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		yeni[i] = line[i];
		i++;
	}
	yeni[i] = '\0';
	return (yeni);
}

char	*put_line(int fd, char *line)
{
	char	*buff;
	int		i;

	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	i = 1;
	while (!ft_strchr(line, '\n') && i != 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
		{
			free(buff);
			return (0);
		}
		buff[i] = '\0';
		line = ft_strjoin(line, buff);
	}
	free (buff);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*a;
	static char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = put_line(fd, line);
	if (line)
	{
		a = newlinedenonce(line);
		line = newlinedensonra(line);
		return (a);
	}
	return (0);
}
/*
int	main(void)
{
	int		fd;
	char	*s;

	fd = open("test.txt", O_RDONLY);
	s = get_next_line(fd);
	while (s)
	{
		printf("%s", s);
		s = get_next_line(fd);
	}
	return (0);
}
*/