/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 12:25:29 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/18 11:53:21 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_read_fd(const int fd, char **s)
{
	int		ret;
	char	*tem1;
	char	buff[BUFF_SIZE + 1];

	if (!(*s))
		*s = ft_strnew(BUFF_SIZE);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		tem1 = ft_strjoin(*s, buff);
		ft_strdel(s);
		*s = tem1;
		if (ft_strchr(*s, '\n'))
			break ;
	}
}

int		get_next_line(const int fd, char **line)
{
	static char	**buff;
	char		*tmp2;
	int			j;
	size_t		i;

	i = 0;
	j = 0;
	if (fd < 0 || read(fd, NULL, 0))
		return (-1);
	if (!buff)
		buff = (char **)malloc(sizeof(char *) * (LIMIT_FD));

	ft_read_fd(fd, &buff[fd]);
	while (buff[fd][i] != '\n' && buff[fd][i] != '\0')
		i++;
	if (i == 0 && buff[fd][i] == '\0')
	{
		*line = ft_strdup("");
		return (0);
	}
	*line = ft_strsub(buff[fd], 0, i);
	if (i == ft_strlen(buff[fd]))
	{
		tmp2 = ft_strdup("");
		ft_strdel(&buff[fd]);
		buff[fd] = tmp2;
		return (1);
	}
	else
	{
		tmp2 = ft_strsub(buff[fd], i + 1, ft_strlen(buff[fd]));
		ft_strdel(&buff[fd]);
		buff[fd] = tmp2;
		return (1);
	}
}
/*
int		main()
{
	int		fd;
	char	*line;
	int		res;

	line = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	fd = open("/Users/agottlie/projects/get_next_line/gnl/sample.txt", O_RDONLY);
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
	res = get_next_line(fd, &line);
	printf("return %d | ", res);
	printf("%s\n", line);
	close(fd);
	return (0);
}
*/
