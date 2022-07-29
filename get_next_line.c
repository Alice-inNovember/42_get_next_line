/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee2 <junlee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:51:24 by junlee2           #+#    #+#             */
/*   Updated: 2022/07/29 11:08:52 by junlee2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <stddef.h>

#include <fcntl.h>
#include <stdio.h>
#include "ft_printf.h"

size_t	ft_strlen(const char *str)
{
	size_t	returni;

	returni = 0;
	while (str[returni])
		returni++;
	return (returni);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*returns;
	size_t	i;

	returns = (char *)malloc(len + 1);
	if (!returns)
		return (0);
	i = 0;
	while (s[start + i] && i < len)
	{
		returns[i] = s[start + i];
		i++;
	}
	returns[i] = 0;
	return (returns);
}

char	*get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	static char	*returns;
}

int	main(void)
{
	int		fd;
	int		i;

	i = 0;
	fd = open("a", O_RDONLY);
	while (i < 20)
	{
		ft_printf("%s", get_next_line(fd));
		i++;
	}
}
