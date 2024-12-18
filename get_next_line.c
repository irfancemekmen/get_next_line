/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iekmen <iekmen@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 20:11:22 by iekmen            #+#    #+#             */
/*   Updated: 2024/12/07 12:38:49 by iekmen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static char	*ft_read(char *str, int fd)
{
	char	*temp;
	int		size;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	size = 1;
	while (!ft_strchr(str, '\n') && size != 0)
	{
		size = read(fd, temp, BUFFER_SIZE);
		if (size == -1)
			return (free(str), str = NULL, free(temp), NULL);
		temp[size] = '\0';
		str = ft_strjoin(str, temp);
		if (!str)
			return (free(temp), NULL);
	}
	free(temp);
	return (str);
}

static char	*ft_line(char *str)
{
	char	*temp;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	temp = malloc(i + 2);
	if (!temp)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		temp[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		temp[i++] = '\n';
	temp[i] = '\0';
	if (i == 0)
		return (free(temp), temp = NULL, temp);
	return (temp);
}

static char	*ft_last(char *str)
{
	char	*temp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (free(str), NULL);
	temp = malloc(ft_strlen(str) - i + 1);
	if (!temp)
		return (free(str), NULL);
	if (str[i] == '\n')
		i++;
	while (str[i])
		temp[k++] = str[i++];
	temp[k] = '\0';
	free(str);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*str = NULL;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	str = ft_read(str, fd);
	if (!str)
		return (free(str), str = NULL, NULL);
	temp = ft_line(str);
	str = ft_last(str);
	return (temp);
}
