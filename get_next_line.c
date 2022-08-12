/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee2 <junlee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:51:24 by junlee2           #+#    #+#             */
/*   Updated: 2022/08/12 16:25:15 by junlee2          ###   ########seoul.kr  */
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

t_strlist	*free_strlist(t_fdlist *fdstruct, int option)
{
	t_strlist	*temp;

	if (option == 'a')
	{

	};
	// {
	// 	while (!fdstruct->strlist)
	// 	{
	// 		temp = fdstruct->strlist->next;
	// 		free(fdstruct->strlist);
	// 		fdstruct->strlist = temp;
	// 	}
	// 	if (fdstruct->prev)
	// 		fdstruct->prev->next = fdstruct->next;
	// 	if (fdstruct->next)
	// 		fdstruct->next->prev = fdstruct->prev;
	// 	free(fdstruct);
	// 	return (0);
	// }
	while (fdstruct->strlist->next)
	{
		temp = fdstruct->strlist->next;
		free (fdstruct->strlist);
		fdstruct->strlist = temp;
	}
	return (0);
}

t_strlist	*read_fd(int fd, t_fdlist *fdstruct, ssize_t *read_cnt)
{
	t_strlist	*temp;

	if (fdstruct->fd == -1)
	{
		fdstruct->strlist = (t_strlist *)malloc(sizeof(t_strlist));
		if (!fdstruct->strlist)
			return (free_strlist(fdstruct, 'a'));
		fdstruct->status = read(fd, fdstruct->strlist->buffer, BUFFER_SIZE);
		if (fdstruct->status <= 0)
			return (free_strlist(fdstruct, 'a'));
		fdstruct->fd = fd;
		return (fdstruct->strlist);
	}
	*read_cnt += 1;
	temp = fdstruct->strlist;
	while (temp->next)
		temp = temp->next;
	temp->next = (t_strlist *)malloc(sizeof(t_strlist));
	if (!temp->next)
		return (free_strlist(fdstruct, 'a'));
	fdstruct->status = read(fd, temp->next, BUFFER_SIZE);
	if (fdstruct->status <= 0)
		return (free_strlist(fdstruct, 'a'));
	return (temp->next);
}

char	*returnstr(t_fdlist *fdstruct, ssize_t start_i, ssize_t read_cnt)
{
	char		*returns;
	ssize_t		total_len;
	ssize_t		i;
	t_strlist	*buffer_list;

	total_len = (BUFFER_SIZE * (read_cnt - 1)) - start_i + fdstruct->index + 1;
	returns = (char *)malloc(total_len + 1);
	if (!returns)
		return (0);
	i = 0;
	buffer_list = fdstruct->strlist;
	while (i < total_len)
	{
		returns[i] = buffer_list->buffer[(start_i + i) % BUFFER_SIZE];
		i++;
		if ((start_i + i) % BUFFER_SIZE == 0)
			buffer_list = buffer_list->next;
	}
	returns[i] = 0;
	free_strlist(fdstruct, 'l');
	fdstruct->index += 1;
	return (returns);
}

char	*get_line(int fd, t_fdlist *fdstruct)
{
	ssize_t		start_i;
	ssize_t		read_cnt;
	t_strlist	*current_buffer;

	start_i = fdstruct->index;
	read_cnt = 1;
	while (1)
	{
		if (fdstruct->index % BUFFER_SIZE == 0)
		{
			read_fd(fd, fdstruct, &read_cnt);
			fdstruct->index = 0;
		}
		current_buffer = find_last_buffer(fdstruct);
		if (!current_buffer)
			return (0);
		while (fdstruct->index < BUFFER_SIZE)
		{
			if (current_buffer->buffer[fdstruct->index] == '\n')
				return (returnstr(fdstruct, start_i, read_cnt));
			else if (fdstruct->index + 1 == fdstruct->status)
				return (returnstr(fdstruct, start_i, read_cnt));
			fdstruct->index++;
		}
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
	return (get_line(fd, fdlist));
}

int	main(void)
{
	int		fd;

	fd = open("a.txt", O_RDONLY);
	while (printf("%s", get_next_line(fd)) != 6);
}
