/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 12:25:29 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/15 16:57:33 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_check_end(char *buff, char **tmp)
{
	int		i;

	i = -1;
	while (buff[++i] != '\n' && buff[i] != '\0')
		;
	(*tmp) = ft_strsub(buff, 0, i);
	if (buff[i] == '\n')
		return (1);
	return (0);
}

char	*ft_buff_trimmer(char *buff)
{
	while (*buff != '\0')
	{
		if (*buff == '\n')
			return (buff + 1);
		++buff;
	}
	if (*buff == '\0')
		return (buff);
	return (NULL);
}

int		ft_read_fd(const int fd, char **buff)
{
	int		ret;
	char	*read_buff;
	char	*new_buff;

	read_buff = ft_strnew(BUFF_SIZE);
	ret = 0;
	while (!(ft_strchr(read_buff, '\n')))
	{
		if (ret == -1)
		{
			free(read_buff);
			return (-1);
		}
		ret = read(fd, read_buff, BUFF_SIZE);
		read_buff[ret] = '\0';
		if (ret == 0 && !(ft_strchr(read_buff, '\n')))
		{
			free(read_buff);
			return (0);
		}
		new_buff = ft_strjoin((*buff), read_buff);
		(*buff) = new_buff;
	}
	free(read_buff);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char	**buff;
	int			j;
	int			gg;

	j = 0;
	if (!buff)
	{
		buff = (char **)malloc(sizeof(char *) * (LIMIT_FD));
		buff[LIMIT_FD - 1] = 0;
	}
	if (!buff || fd < 0 || line == NULL || read(fd, NULL, 0))
		return (-1);

	if (buff[fd] == NULL)
		buff[fd] = ft_strnew(BUFF_SIZE);

	if (ft_read_fd(fd, &buff[fd]) == -1)
		return (-1);

	gg = ft_check_end(buff[fd], line);

	buff[fd] = ft_buff_trimmer(buff[fd]);

	while (((*line)[j] != '\0') && j < 2)
		++j;
	return (((j > 0) || (gg > 0)) ? 1 : 0);
}
/*
int		main(int ac, char **av)
{
	int		fd;
	char	*line;
	int		res;

	res = ac;
	line = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	fd = open(av[1], O_RDONLY);
	printf("%d\n", fd);
	if (fd < 0)
	{
		printf("Wrong name of file\n");
		return (-1);
	}
	while ((res = get_next_line(fd, &line)))
	{
		printf("return %d | ", res);
		printf("%s\n", line);
	}
	res = get_next_line(fd, &line);
	printf("return %d | ", res);
	printf("%s\n", line);
	close(fd);
	return (0);
}

*/