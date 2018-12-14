/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 12:25:29 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/14 10:41:55 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_check_end(char *buff, char **tmp)		//	вставляет в tmp обрезанную до '\n' из buff строку
{
	int		i;

	i = -1;
	while (buff[++i] != '\n' && buff[i] != '\0')		//	добавить EOF
		;
	(*tmp) = ft_strsub(buff, 0, i);
	if (buff[i] == '\n')
		return (1);
	return (0);
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
		if (ret == -1)
			return (-1);
		ft_bzero(read_buff, BUFF_SIZE);
		ret = read(fd, read_buff, BUFF_SIZE);
		read_buff[ret] = '\0';
		if (ret == 0 && !(ft_strchr(read_buff, '\n')))
			return (0);
		(*buff) = ft_strjoin((*buff), read_buff);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char	*buff;
	char		*tmp;
	int			i;
	int			j;
	int gg;

	j = 0;
	tmp = ft_strnew(BUFF_SIZE);
	if (!buff)
	{
		buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
		buff[BUFF_SIZE] = '\0';
	}

	if (!buff || fd < 0 || line == NULL || read(fd, NULL, 0))		//	проверка на валидность
		return (-1);

	i = ft_read_fd(fd, &buff);							//	чтение файла
	if (i == -1)
		return (-1);
	// printf("buff\n%s\n", buff);
	gg = ft_check_end(buff, &tmp);							//	вставляет в tmp обрезанную до '\n' из buff строку
	buff = ft_buff_trimmer(buff);						//	возвращает обрезанный buff
	// printf("tmp\n%s\n", tmp);
	(*line) = tmp;
	while ((tmp[j] != '\0' || buff[j] != '\0') && j < 2)
		++j;
	if (j > 0 || i == 1)
		return (1);
	return (gg);
}
/*
int		main(int ac, char **av)
{
	int		fd;
	char	*line;
	int		b;

	fd = 0;
	b = ac;
	line = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
		{
			printf("Wrong name of file\n");
			return (-1);
		}
		while ((b = get_next_line(fd, &line)))
		{
			printf("return %d | ", b);
			printf("%s\n", line);
			free(line);
		}
		b = get_next_line(fd, &line);
		printf("return %d | ", b);
		printf("%s\n", line);
	}
	else
	printf("Give me a name of file\n");
	close(fd);
	return (0);
}
*/