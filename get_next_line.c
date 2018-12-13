/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 12:25:29 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/13 10:31:24 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_check_end(char *buff, char **tmp)		//	вставляет в tmp обрезанную до '\n' из buff строку
{
	int		i;

	i = -1;
	while (buff[++i] != '\n' && buff[i] != '\0')		//	добавить EOF
		;
	(*tmp) = ft_strsub(buff, 0, i);
}

char	*ft_buff_trimmer(char *buff)		//	аналог strchr. Возвращает обрезанный buff
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

	read_buff = ft_strnew(BUFF_SIZE);
	while (!(ft_strchr(read_buff, '\n')))
	{
		ret = read(fd, read_buff, BUFF_SIZE);
		(*buff) = ft_strjoin((*buff), read_buff);
	}
	if (ret == -1)							//	проверка на чтение
		return (-1);
	else if (ret > 0)
		return (1);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static char	*buff;
	char		*tmp;

	tmp = ft_strnew(BUFF_SIZE);
	if (!buff)
	{
		buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
		buff[BUFF_SIZE] = '\0';
	}
	else
		printf("after buff\n%s\n", buff);
	if (!buff || fd < 0 || line == NULL || read(fd, NULL, 0))		//	проверка на валидность
		return (-1);
	if (ft_read_fd(fd, &buff) == 0)									//	чтение файла
	{
		ft_check_end(buff, &tmp);
		return (0);
	}
	printf("buff\n%s\n", buff);
	ft_check_end(buff, &tmp);										//	вставляет в tmp обрезанную до '\n' из buff строку
	buff = ft_buff_trimmer(buff);									//	возвращает обрезанный buff
	printf("tmp\n%s\n", tmp);
	(*line) = tmp;
	return (0);
}

int		main(int ac, char **av)
{
	int		fd;
	char	*line;

	fd = 0;
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
		// printf("%s\n", line);
		get_next_line(fd, &line);
		get_next_line(fd, &line);
		get_next_line(fd, &line);
		get_next_line(fd, &line);
		get_next_line(fd, &line);
		get_next_line(fd, &line);
		// get_next_line(fd, &line);
	}
	else
		printf("Give me a name of file\n");
	close(fd);
	return (0);
}
