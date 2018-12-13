/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 14:32:06 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/12 12:20:29 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_trim(char **line, char *buff, const int fd)
{
	size_t	i;
	char	*tmp;
	int		ret;

	i = -1;
	tmp = ft_strnew(BUFF_SIZE);
	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		buff[ret] = '\0';
		tmp = ft_strjoin(tmp, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	while (tmp[++i] != '\n' && tmp[i] != '\0')
		;
	(*line) = ft_strsub(tmp, 0, i);
	buff = ft_strchr(tmp, '\n');
	buff = buff + 1;
	printf("line = %s\n", (*line));
	return (buff);
	// printf("buff = %s\n", ft_strchr(buff, '\n'));
	// return (*line);
}

int		get_next_line(const int fd, char **line)
{
	static char	**buff;
	int			i;

	i = 0;
	if (buff == NULL)
	{
		buff = (char **)malloc(sizeof(char *) * (LIMIT_FD + 1));
		buff[LIMIT_FD] = 0;
	}
	if (buff[fd])
	{
		// while (buff[fd][++i] != '\n' && buff[fd][i] != '\0')
			// ;
		// buff[fd] = ft_strchr(buff[fd], '\n');
		// buff[fd]++;
		// (*line) = ft_strsub(buff[fd], 0, i);
		// buff[fd] = ft_strchr(buff[fd], '\n');
		return (0);
	}
	if (!buff || fd < 0 || line == NULL || read(fd, NULL, 0))
		return (-1);
	if (buff[fd] == NULL)
		buff[fd] = ft_strnew(BUFF_SIZE);
		;
	// printf("line = %s\n", *line);
	buff[fd] = ft_read_trim(line, buff[fd], fd);
	printf("buff_fd = %s", buff[fd]);
	return (0);
}

int		main(int ac, char **av)
{
	int		fd;
	char	*line;

	line = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
		{
			printf("Wrong name of file\n");
			return (-1);
		}
		get_next_line(fd, &line);
		printf("| %s\n", line);
		get_next_line(fd, &line);
		printf("| %s\n", line);
		get_next_line(fd, &line);
		printf("| %s\n", line);
		// get_next_line(fd, &line);
		// printf("| %s\n", line);
		// get_next_line(fd, &line);
		// get_next_line(fd, &line);
	}
	else
		printf("Give me a name of file\n");
	return (0);
}
