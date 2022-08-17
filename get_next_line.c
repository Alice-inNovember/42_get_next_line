/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee2 <junlee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:51:24 by junlee2           #+#    #+#             */
/*   Updated: 2022/08/17 14:52:43 by junlee2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

#include <fcntl.h>
#include <stdio.h>

t_fdlist	*find_fd(int fd, t_fdlist *fdlist)
{
	t_fdlist	*origin;
	t_fdlist	*returnfd;

	origin = fdlist;
	while (fdlist)
	{
		if (fdlist->fd == fd)
			return (fdlist);
		fdlist = fdlist->next;
	}
	returnfd = (t_fdlist *)malloc(sizeof(t_fdlist));
	if (!returnfd)
		return (0);
	returnfd->fd = -1;
	returnfd->index = 0;
	returnfd->next = origin;
	if (origin)
		origin->prev = returnfd;
	returnfd->prev = 0;
	returnfd->status = 0;
	returnfd->strlist = 0;
	return (returnfd);
}

t_strlist	*find_last_buffer(t_fdlist *fdstruct)
{
	t_strlist	*temp;

	temp = fdstruct->strlist;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

ssize_t	strlist_init(int fd, t_fdlist *fdlist)
{
	if (fdlist->fd != -1)
		return (fdlist->status);
	fdlist->strlist = (t_strlist *)malloc(sizeof(t_strlist));
	if (!fdlist->strlist)
		return (-1);
	fdlist->fd = fd;
	fdlist->status = read(fd, fdlist->strlist->buffer, BFSIZE);
	fdlist->strlist->next = 0;
	return (fdlist->status);
}

ssize_t	strlist_read(t_fdlist *fdlist, t_strlist *buffer, ssize_t *readcnt)
{
	buffer->next = (t_strlist *)malloc(sizeof(t_strlist));
	if (!fdlist->strlist)
		return (-1);
	fdlist->status = read(fdlist->fd, buffer->next->buffer, BFSIZE);
	buffer->next->next = 0;
	*readcnt += 1;
	return (fdlist->status);
}

char	*make_str(t_fdlist *fdlist, ssize_t s_idx, ssize_t readcnt, int option)
{
	char		*returns;
	t_strlist	*strlist;
	ssize_t		totallen;
	ssize_t		i;
	ssize_t		j;

	fdlist->index++;
	if (fdlist->index + 1 == BFSIZE)
	{
		fdlist->index = 0;
		strlist_read(fdlist, find_last_buffer(fdlist), &readcnt);
	}
	totallen = (BFSIZE - s_idx) + (BFSIZE * readcnt) - (BFSIZE - fdlist->index);
	returns = (char *)malloc(totallen + 1);
	i = 0;
	strlist = fdlist->strlist;
	while (i < totallen)
	{
		j = s_idx;
		while (j < BUFFER_SIZE && i < totallen)
		{
			returns[i] = strlist->buffer[j];
			i++;
			j++;
		}
		strlist = strlist->next;
	}
	returns[i] = 0;
	fdlist->strlist = find_last_buffer(fdlist);
	return (returns);
}

char	*next_line(int fd, t_fdlist *fdlist)
{
	ssize_t		status;
	ssize_t		st_idx;
	ssize_t		readcnt;
	t_strlist	*currunt_buff;

	status = strlist_init(fd, fdlist);
	st_idx = fdlist->index;
	readcnt = 0;
	while (1)
	{
		currunt_buff = find_last_buffer(fdlist);
		if (status == 0)
			return (make_str(fdlist, st_idx, readcnt, 'E'));
		while (fdlist->index + 1 <= status)
		{
			if (currunt_buff->buffer[fdlist->index] == '\n')
				return (make_str(fdlist, st_idx, readcnt, 'N'));
			fdlist->index++;
			//ssize_t	debug = fdlist->index;
		}
		if (fdlist->index + 1 == BFSIZE)
			fdlist->index = 0;
		status = strlist_read(fdlist, currunt_buff, &readcnt);
	}
}

char	*get_next_line(int fd)
{
	static t_fdlist	*fdlist = 0;

	if (fd < 0)
		return (0);
	fdlist = find_fd(fd, fdlist);
	if (!fdlist)
		return (0);
	return (next_line(fd, fdlist));
}

int	main(void)
{
	int		fd;

	fd = open("a.txt", O_RDONLY);
	while (printf("%s", get_next_line(fd)) != 6);
}
