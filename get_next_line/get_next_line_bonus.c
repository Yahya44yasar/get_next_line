/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyasar <yyasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 01:05:25 by yyasar            #+#    #+#             */
/*   Updated: 2022/12/10 11:53:30 by yyasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*newlinedansonra_line(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	new = (char *)malloc(sizeof(char) * ((ft_strlen(str) - i) + 1));
	if (!new)
		return (NULL);
	i++;
	while (str[i])
		new[j++] = str[i++];
	new[j] = '\0';
	free(str);
	return (new);
}

char	*newlinedanonce_line(char *str)
{
	int		sayac;
	char	*yeni_str;

	sayac = 0;
	if (!str[sayac])
		return (NULL);
	while (str[sayac] != '\n' && str[sayac] != '\0')
		sayac++;
	yeni_str = (char *)malloc(sizeof(char) * (sayac + 2));
	if (!yeni_str)
		return (NULL);
	sayac = 0;
	while (str[sayac] && str[sayac] != '\n')
	{
		yeni_str[sayac] = str[sayac];
		sayac++;
	}
	if (str[sayac] == '\n')
	{
		yeni_str[sayac] = str[sayac];
		sayac++;
	}
	yeni_str[sayac] = '\0';
	return (yeni_str);
}

char	*putline(int fd, char *line)
{
	char	*buff;
	int		i;

	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	i = 1;
	while (!ft_strchr(line, '\n') && i != 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[i] = '\0';
		line = ft_strjoin(line, buff);
	}
	free(buff);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line[4096];
	char		*s;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line[fd] = putline(fd, line[fd]);
	if (line[fd])
	{
		s = newlinedanonce_line(line[fd]);
		line[fd] = newlinedansonra_line(line[fd]);
		return (s);
	}
	return (NULL);
}

/*
int	main(void)
{
	int	i;
	int	s[3];

	int fd = open("test.txt", O_RDONLY);
	int fd2 = open("test2.txt", O_RDONLY);
	int fd3 = open("test3.txt", O_RDONLY);
	s[0] = fd;
	s[1] = fd2;
	s[2] = fd3;
	i = 0;
	char **str;

	str = (char **)malloc(sizeof(char *) * 20);
	while (i < 3)
	{
		str[i] = get_next_line(s[i]);
		while (str[i])
		{	
			write(1, str[i], ft_strlen(str[i]));
			str[i] = get_next_line(s[i]);
		}
		i++;
	}
	return (0);
}
*/