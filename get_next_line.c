/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee2 <junlee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:51:24 by junlee2           #+#    #+#             */
/*   Updated: 2022/08/01 16:13:05 by junlee2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

#include <fcntl.h>
#include "ft_printf.h"

void	ft_lstclear(t_strlist *lst)
{
	t_strlist	*temp;

	while (lst)
	{
		temp = lst->next;
		free(lst);
		lst=temp;
	}
}

t_fdlist	*findlist(int fd, t_fdlist **list)
{
	t_fdlist	*temp;

	temp = *list;
	if (temp == 0)
	{
		*list = (t_fdlist *)malloc(sizeof(t_fdlist));
		if (*list)
			(*list)->fd = -1;
		return (*list);
	}
	while (!temp->next)
	{
		if (temp->fd == fd)
			return(temp);
		temp = temp->next;
	}
	temp->next = (t_fdlist *)malloc(sizeof(t_fdlist));
	if (*list)
		(*list)->fd = -1;
	return (temp->next);
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

int	readfd(int fd, t_fdlist *fdlist, size_t *status, t_strlist *strlist)
{
	*status = read(fd, fdlist->buffer, BUFFER_SIZE);
	if (*status == 0 || *status == -1)
		return (-1);
	
	fdlist->index = 0;
	return (0);
}

char	*next_line(int fd, t_fdlist *fdlist)
{
	size_t	status;
	t_strlist	*strlist;

	if (fdlist->fd == -1)
		if (readfd(fd, fdlist, &status, strlist))
			return (-1);
	while (1)
	{
		while (fdlist->buffer[fdlist->index] == '\n' && fdlist->index < BUFFER_SIZE)
			fdlist->index++;
		if (fdlist->index == BUFFER_SIZE)
			if (readfd(fd, fdlist, &status, strlist))
				return (-1);
	}
	
}

char	*get_next_line(int fd)
{
	static t_fdlist	*fdlist = 0;
	t_fdlist		*workbench;
	
	if (fd < 0)
		return ((void *)0);
	workbench = findlist(fd, fdlist);
	if (!workbench)
		return ((void *)0);
	next_line(fd, workbench);
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
