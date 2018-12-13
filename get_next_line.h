/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 14:34:02 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/13 10:34:02 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 16
# define LIMIT_FD 11000

#include <sys/types.h>		//	содержит тип mode_t.
#include <fcntl.h>			//	содержит функции open, read и т.д.
#include <unistd.h>			//	содержит функцию close
#include <stdlib.h>			//	содержит функцию malloc и free
#include <stdio.h>			//	для тестов. УДАЛИТЬ ПЕРЕД ПУШЕМ
#include "libft/libft.h"	//	для тестов. УДАЛИТЬ ПЕРЕД ПУШЕМ

int	get_next_line(const int fd, char **line);

#endif
