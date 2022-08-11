/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee2 <junlee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:51:24 by junlee2           #+#    #+#             */
/*   Updated: 2022/08/11 15:30:25 by junlee2          ###   ########seoul.kr  */
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

char	*returnstr(t_fdlist *workbench, int readcnt, size_t startindex, int op)
{
	return ((void *)0);
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
		startindex = workbench->index;
		while (workbench->index < BUFFER_SIZE)
		{
			if (buffer[workbench->index] == '\n')
				return (returnstr(workbench, readcnt, startindex, 1));
			else if (workbench->index == workbench->status)
				return (returnstr(workbench, readcnt, startindex, 0));
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
