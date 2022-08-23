/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee2 <junlee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:58:22 by junlee2           #+#    #+#             */
/*   Updated: 2022/08/23 15:01:13 by junlee2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 10
# define BFSIZE BUFFER_SIZE

# include <stdlib.h>
# include <unistd.h>

typedef struct s_fdlist
{
	int				fd;
	char			buffer[BUFFER_SIZE];
	ssize_t			totallen;
	ssize_t			s_idx;
	ssize_t			l_idx;
	struct s_fdlist	*next;
	struct s_fdlist	*prev;
}	t_fdlist;

typedef struct s_buffer
{
	char	buffer[BUFFER_SIZE];
	ssize_t	stack;
	ssize_t	idx;
	ssize_t	s_idx;
	ssize_t	l_idx;
}	t_buffer;


t_fdlist	*find_fd(int fd, t_fdlist *fdlist);

#endif
