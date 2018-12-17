/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 12:25:29 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/17 15:45:15 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_check_end(char **tmp)
{
	int		i;

	i = -1;
	while ((*tmp)[++i] != '\n' && (*tmp)[i] != '\0')
		;
	(*tmp) = ft_strsub((*tmp), 0, i);
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

int		ft_read_fd(const int fd, char **buff, char **line_copy)
{
	int		ret;
	char	*read_buff;
	// char	*new_buff;

	read_buff = ft_strnew(BUFF_SIZE);
	ret = 0;
	while (!(ft_strchr((*buff), '\n')))
	{
		ret = read(fd, (*buff), BUFF_SIZE);
		(*buff)[ret] = '\0';

		if (ret == 0 && !(ft_strchr((*buff), '\n')))
			return (0);
		if (ret == -1)
			return (-1);

		read_buff = ft_strjoin((*line_copy), (*buff));
		free(*line_copy);
		(*line_copy) = read_buff;
	}
	// printf("line = %s\n", line_copy);
	// printf("buff = %s\n", *buff);
	// free(read_buff);
	return (1);
}

/*int		ft_solver(char **buff, char *tmp, int fd)
{
	if (buff[fd][0] == '\0')					//	если буф пустой
	{
		ft_read_fd(fd, &buff[fd], &tmp);		//	читаем в буф и кидаем в line строку до '\n'
		ft_check_end(&tmp);
		buff[fd] = ft_buff_trimmer(buff[fd]);
	}
	else if (ft_strcmp(buff[fd], "\0") != 0)	//	иначе если буф не пустой
	{
		while (buff[fd][++i] != '\0')			//	иначе если buff не пустой
			if (buff[fd][i] == '\n')			//	и имеет '\n'
			{
				y++;
				break ;
			}
		if (y > 0)								//	имеет '\n'
		{
			ft_check_end(&tmp);					//	закидываем в line строку до '\n'
			buff[fd] = ft_buff_trimmer(buff[fd]);
		}
		else									//	иначе (буф не пустой, но не имеет '\n')
		{
			ft_read_fd(fd, &buff[fd], &tmp);
			ft_check_end(&tmp);
			buff[fd] = ft_buff_trimmer(buff[fd]);
		}
	}
}
*/
int		get_next_line(const int fd, char **line)
{
	static char	**buff;
	char		*tmp;
	int			j;
	int			gg;
	int			y;
	int			i;

	j = 0;
	y = 0;
	gg = 0;
	i = -1;
	if (!buff)
	{
		buff = (char **)malloc(sizeof(char *) * (LIMIT_FD));
		buff[LIMIT_FD - 1] = 0;
	}
	if (!buff || fd < 0 || line == NULL || read(fd, NULL, 0))
		return (-1);

	if (buff[fd] == NULL)
		buff[fd] = ft_strnew(BUFF_SIZE);

	tmp = ft_strdup(buff[fd]);
	if (buff[fd][0] == '\0')					//	если буф пустой
	{
		ft_read_fd(fd, &buff[fd], &tmp);		//	читаем в буф и кидаем в line строку до '\n'
		ft_check_end(&tmp);
		buff[fd] = ft_buff_trimmer(buff[fd]);
	}
	else if (ft_strcmp(buff[fd], "\0") != 0)	//	иначе если буф не пустой
	{
		while (buff[fd][++i] != '\0')			//	иначе если buff не пустой
			if (buff[fd][i] == '\n')			//	и имеет '\n'
			{
				y++;
				break ;
			}
		if (y > 0)								//	имеет '\n'
		{
			ft_check_end(&tmp);					//	закидываем в line строку до '\n'
			buff[fd] = ft_buff_trimmer(buff[fd]);
		}
		else									//	иначе (буф не пустой, но не имеет '\n')
		{
			ft_read_fd(fd, &buff[fd], &tmp);
			ft_check_end(&tmp);
			buff[fd] = ft_buff_trimmer(buff[fd]);
		}
	}
	(*line) = tmp;

/*
	if (ft_read_fd(fd, &buff[fd], tmp) == -1)
		return (-1);
	// printf("buff == %s\n", buff[fd]);
	// printf("line == %s\n", *line);
	gg = ft_check_end(buff[fd], line);

	buff[fd] = ft_buff_trimmer(buff[fd]);*/

	while (((*line)[j] != '\0') && j < 2)
		++j;
	return (((j > 0) || (gg > 0)) ? 1 : 0);
}

/*int		main(int ac, char **av)
{
	int		fd;
	char	*line;
	int		res;

	res = ac;
	line = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Wrong name of file\n");
		return (-1);
	}
	// while ((res = get_next_line(fd, &line)))
	// {
		// printf("return %d | ", res);
		// printf("%s\n", line);
	// }
	res = get_next_line(fd, &line);
	printf("return | %s", line);
	printf("\n");
	printf("\n");
	res = get_next_line(fd, &line);
	printf("return | %s", line);
	printf("\n");
	printf("\n");
	res = get_next_line(fd, &line);
	printf("return | %s", line);
	printf("\n");
	printf("\n");
	res = get_next_line(fd, &line);
	printf("return | %s", line);
	printf("\n");
	printf("\n");
	res = get_next_line(fd, &line);
	printf("return | %s", line);
	printf("\n");
	printf("\n");
	res = get_next_line(fd, &line);
	printf("return | %s", line);
	printf("\n");
	printf("\n");
	res = get_next_line(fd, &line);
	printf("return | %s", line);
	printf("\n");
	printf("\n");
	res = get_next_line(fd, &line);
	printf("return | %s", line);
	printf("\n");
	printf("\n");
	res = get_next_line(fd, &line);
	printf("return | %s", line);
	printf("\n");
	printf("\n");
	res = get_next_line(fd, &line);
	printf("return | %s", line);
	// res = get_next_line(fd, &line);
	// printf("%s\n", line);
	close(fd);
	return (0);
}*/


int		main()
{
	int		fd;
	char	*line;
	int		res;


	line = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	fd = open("/Users/agottlie/projects/get_next_line/gnl/some.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Wrong name of file\n");
		return (-1);
	}
	/*while ((res = get_next_line(fd, &line)))
	{
		// printf("return %d | ", res);
		// printf("%s\n", line);
	}*/
	res = get_next_line(fd, &line);
	printf("return | %s", line);
	printf("\n");
	printf("\n");
	res = get_next_line(fd, &line);
	printf("return | %s", line);
	printf("\n");
	printf("\n");
	res = get_next_line(fd, &line);
	printf("return | %s", line);
	printf("\n");
	printf("\n");
	res = get_next_line(fd, &line);
	printf("return | %s", line);
	printf("\n");
	printf("\n");
	res = get_next_line(fd, &line);
	printf("return | %s", line);
	printf("\n");
	printf("\n");
	res = get_next_line(fd, &line);
	printf("return | %s", line);
	printf("\n");
	printf("\n");
	res = get_next_line(fd, &line);
	printf("return | %s", line);
	printf("\n");
	printf("\n");
	res = get_next_line(fd, &line);
	printf("return | %s", line);
	printf("\n");
	printf("\n");
	res = get_next_line(fd, &line);
	printf("return | %s", line);
	printf("\n");
	printf("\n");
	res = get_next_line(fd, &line);
	printf("return | %s", line);
	// res = get_next_line(fd, &line);
	// printf("%s\n", line);
	close(fd);
	return (0);
}
