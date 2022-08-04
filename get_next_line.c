/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee2 <junlee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:51:24 by junlee2           #+#    #+#             */
/*   Updated: 2022/08/04 17:25:31 by junlee2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

#include <fcntl.h>
#include <stdio.h>

void	freelist(t_fdlist *fdlist)
{
	t_strlist	*temp;

	while (fdlist->strlist->next != 0)
	{
		temp = fdlist->strlist->next;
		free (fdlist->strlist);
		fdlist->strlist = temp;
	}
	fdlist->index++;
}

t_fdlist	*find_list(t_fdlist **fdlist, int fd)
{
	t_fdlist	*temp;

	temp = *fdlist;
	while (*fdlist != 0)
	{
		if (fd == (*fdlist)->fd)
		{
			(*fdlist)->size = 0;
			return (*fdlist);
		}
		(*fdlist) = (*fdlist)->next;
	}
	*fdlist = (t_fdlist *)malloc(sizeof(t_fdlist));
	if (!*fdlist)
		return (0);
	(*fdlist)->fd = -1;
	(*fdlist)->index = 0;
	(*fdlist)->size = 0;
	(*fdlist)->next = temp;
	return (*fdlist);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (dst == 0 && src == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

int	readnext(int fd, t_fdlist *fdlist, size_t *status)
{
	t_strlist	*origin;
	t_strlist	*pre;

	origin = fdlist->strlist;
	while (fdlist->strlist)
	{
		pre = fdlist->strlist;
		fdlist->strlist = fdlist->strlist->next;
	}
	if (fdlist->fd == -1)
		fdlist->strlist = (t_strlist *)malloc(sizeof(t_strlist));
	else
	{
		pre->next = (t_strlist *)malloc(sizeof(t_strlist));
		fdlist->strlist = pre->next;
	}
	if (!fdlist->strlist)
		return (-1);
	*status = read(fd, fdlist->strlist->buffer, BUFFER_SIZE);
	if (*status == -1 || *status == 0)
		return (*status);
	if (fdlist->fd != -1)
		fdlist->strlist = origin;
	fdlist->fd = fd;
	return (0);
}

char	*cpystr(t_fdlist *fdlist, size_t size, size_t i)
{
	char		*returns;
	t_strlist	*temp;

	returns = (char *)malloc(size + 1);
	if (!returns)
		return (0);
	temp = fdlist->strlist;
	while (i < size)
	{
		returns[i] = temp->buffer[i % BUFFER_SIZE];
		i++;
		if (i % BUFFER_SIZE == 0)
			temp = temp->next;
	}
	returns[size] = 0;
	freelist(fdlist);
	return (returns);
}

char	*nextline(int fd, t_fdlist *fdlist)
{
	size_t		status;
	size_t		start;
	t_strlist	*temp;

	if (fdlist->fd == -1)
		if (readnext(fd, fdlist, &status) == -1)
			return (0);
	temp = fdlist->strlist;
	while (1)
	{	
		start = fdlist->index;
		while (1)
		{
			if (fdlist->index == BUFFER_SIZE)
				break ;
			if (temp->buffer[fdlist->index] == '\n')
				return (cpystr(fdlist, fdlist->size + fdlist->index - start + 1, start));
			if (fdlist->index == status)
				return (cpystr(fdlist, fdlist->size + fdlist->index - start, start));
			fdlist->index++;
		}
		if (readnext(fd, fdlist, &status) == -1)
		{
			//freelist();
			return (0);
		}
		temp = temp->next;
		fdlist->size += BUFFER_SIZE;
		fdlist->index = 0;
	}
	return (0);
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

int main()
{
	char a[BUFFER_SIZE];
	int	fd = open("a.txt", O_RDONLY);
	// read(fd, a, BUFFER_SIZE);
	// write(1, a, BUFFER_SIZE);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
}