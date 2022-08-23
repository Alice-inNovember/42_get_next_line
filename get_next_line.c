/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee2 <junlee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:51:24 by junlee2           #+#    #+#             */
/*   Updated: 2022/08/23 15:01:12 by junlee2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <fcntl.h>
#include <stdio.h>

t_fdlist	*find_fd(int fd, t_fdlist *fdlist)
{
	t_fdlist	*fdnode;

	fdnode = fdlist;
	while (fdnode->next != 0)
	{
		if (fdnode->fd == fd)
			return (fdnode);
		fdnode = fdnode->next;
	}
	fdnode->next = (t_fdlist *)malloc(sizeof(t_fdlist));
	if (!fdnode->next)
		return (0);
	fdnode->next->fd = fd;
	fdnode->next->totallen = 0;
	fdnode->next->s_idx = -1;
	fdnode->next->next = 0;
	fdnode->next->prev = fdnode;
	return (fdnode->next);
}

void	buffer_init(t_fdlist *fdlist, t_buffer *buff, ssize_t stack)
{
	ssize_t	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		buff->buffer[i] = fdlist->buffer[i];
		i++;
	}
	buff->stack = stack;
	buff->idx = fdlist->s_idx;
	buff->s_idx = fdlist->s_idx;
	buff->l_idx = fdlist->l_idx;
}

void	cpybuffer(t_buffer buff, char *returnstr, ssize_t e_idx, char option)
{
	ssize_t	idx;

	if (!returnstr)
		return ;
	idx = buff.s_idx;
	while (buff.idx <= e_idx)
	{
		returnstr[buff.idx + buff.stack * BUFFER_SIZE] = buff.buffer[buff.idx];
		buff.idx++;
	}
	if (option == 'Y')
		returnstr[buff.idx + buff.stack * BUFFER_SIZE] = 0;
}

char	*get_line(t_fdlist *fdlist, ssize_t stack)
{
	t_buffer	buff;
	char		*returnstr;
	
	buffer_init(fdlist, &buff, stack);
	while (buff.idx < buff.l_idx)
	{
		fdlist->totallen++;
		if (buff.buffer[buff.idx] == '\n')
		{
			returnstr = (char *)malloc(fdlist->totallen + 1);
			cpybuffer(buff, returnstr, buff.idx, 'Y');
			return (returnstr);
		}
		buff.idx++;
	}
	fdlist->s_idx = 0;
	fdlist->l_idx = read(fdlist->fd, fdlist->buffer, BUFFER_SIZE);
	returnstr = get_line(fdlist, stack + 1);
	cpybuffer(buff, returnstr, buff.idx, 'Y');
	return (returnstr);
}

char	*get_next_line(int fd)
{
	static t_fdlist	*fdhead = 0;
	static t_fdlist	*workbench;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!fdhead)
	{
		fdhead = (t_fdlist *)malloc(sizeof(t_fdlist));
		if (!fdhead)
			return (0);
		fdhead->fd = -1;
		fdhead->next = 0;
	}
	workbench = find_fd(fd, fdhead);
	if (!workbench)
		return (0);
	workbench->s_idx = 0;
	workbench->l_idx = read(workbench->fd, workbench->buffer, BUFFER_SIZE);
	return (get_line(workbench, 0));
}

int	main(void)
{
	int		fd;
	char	*debugstr;

	fd = open("a.txt", O_RDONLY);
	debugstr = get_next_line(fd);
	printf("%s", debugstr);
	//while (printf("%s", get_next_line(fd)) != 6){}
}
