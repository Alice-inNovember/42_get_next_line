/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee2 <junlee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:51:24 by junlee2           #+#    #+#             */
/*   Updated: 2022/08/11 16:48:59 by junlee2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

#include <fcntl.h>
#include <stdio.h>

t_fdlist	*find_list(t_fdlist **fdlist, int fd)
{
	t_fdlist	temp;
	t_fdlist	*find;
	t_fdlist	*pre;

	temp.fd = -1;
	temp.next = *fdlist;
	find = &temp;
	while (find != 0)
	{
		if (find->fd == fd)
			return (find);
		pre = find;
		find = find->next;
	}
	find = (t_fdlist *)malloc(sizeof(t_fdlist));
	pre->next = find;
	if (!find)
		return ((void *)0);
	find->fd = -1;
	find->index = 0;
	find->next = 0;
	find->strlist = 0;
	return (find);
}

int	readfd(int fd, t_fdlist *workbench, char *buffer)
{
	t_strlist	temp;
	t_strlist	*find;
	t_strlist	*pre;

	temp.next = workbench->strlist;
	find = &temp;
	while (find != 0)
	{
		pre = find;
		find = find->next;
	}
	find = (t_fdlist *)malloc(sizeof(t_fdlist));
	pre->next = find;
	if (!find)
	{
		free_strlist();
		return (-1);
	}
	workbench->status = read(fd, find->buffer, BUFFER_SIZE);
	buffer = find->buffer;
	return (0);
}

char	*returnstr(t_fdlist *workbench, int readcnt, size_t startindex)
{
	size_t		totallen;
	char		*returns;
	t_fdlist	*strlist;
	size_t		i;

	if (readcnt == 0)
		totallen = workbench->index - startindex + 1;
	else
		totallen = ((BUFFER_SIZE * (readcnt + 1)) - (startindex + 1)) + workbench->index + 1;
	returns = malloc(totallen + 1);
	if (!returns)
		return ((void *)0);
	strlist = workbench->strlist;
	i = 0;
	while (/* condition */)
	{
		/* code */
	}
	return (returns);
}

char	*nextline(int fd, t_fdlist *workbench)
{
	int		readcnt;
	size_t	startindex;
	char	*buffer;

	readcnt = 0;
	if (workbench->fd == -1)
		if (readfd(fd, workbench, buffer) == -1)
			return ((void *)0);
	while (workbench->status != 0 && workbench->status != -1)
	{
		while (workbench->index < BUFFER_SIZE)
		{
			if (buffer[workbench->index] == '\n')
				return (returnstr(workbench, readcnt, startindex));
			else if (workbench->index == workbench->status)
				return (returnstr(workbench, readcnt, startindex));
			workbench->index += 1;
		}
		if (readfd(fd, workbench, buffer) == -1)
			return ((void *)0);
		workbench->index = 0;
	}
	return ((void *)0);
}

char	*get_next_line(int fd)
{
	static t_fdlist	*fdlist = 0;
	t_fdlist		*workbench;

	if (fd < 0)
		return ((void *)0);
	workbench = find_list(&fdlist, fd);
	if (!workbench)
		return ((void *)0);
	return (nextline(fd, workbench));
}

int	main(void)
{
	char	a[BUFFER_SIZE];
	int		fd;

	fd = open("a.txt", O_RDONLY);
	while (printf("%s", get_next_line(fd)) != 6)
		printf("\n");
}
