/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee2 <junlee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:58:22 by junlee2           #+#    #+#             */
/*   Updated: 2022/08/24 15:53:56 by junlee2          ###   ########seoul.kr  */
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
	ssize_t			stack;
	ssize_t			s_idx;
	ssize_t			c_idx;
	ssize_t			e_idx;
	ssize_t			indent;
	struct s_fdlist	*next;
	struct s_fdlist	*prev;
}	t_fdlist;

void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif
