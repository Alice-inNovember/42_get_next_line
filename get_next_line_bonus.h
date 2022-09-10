/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee2 <junlee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:58:22 by junlee2           #+#    #+#             */
/*   Updated: 2022/08/29 11:03:50 by junlee2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# define BUFFER_SIZE 10

typedef struct s_fdlist
{
	int				fd;
	char			buffer[BUFFER_SIZE];
	ssize_t			totallen;
	ssize_t			stack;
	ssize_t			s_idx;
	ssize_t			c_idx;
	ssize_t			status;
	ssize_t			indent;
	struct s_fdlist	*next;
	struct s_fdlist	*prev;
}	t_fdlist;

char		*get_next_line(int fd);
t_fdlist	*find_fd(int fd, t_fdlist *fdlist);
char		*get_line_re(t_fdlist	*fdlist);
char		*free_fdlist(t_fdlist *fdlist);
void		*ft_memcpy(void *dst, const void *src, size_t n);

#endif
