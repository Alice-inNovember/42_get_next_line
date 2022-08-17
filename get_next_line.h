/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee2 <junlee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:58:22 by junlee2           #+#    #+#             */
/*   Updated: 2022/08/17 13:16:35 by junlee2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 10
# define BFSIZE BUFFER_SIZE

typedef struct s_strlist
{
	char				buffer[BUFFER_SIZE];
	struct s_strlist	*next;
}	t_strlist;

typedef struct s_fdlist
{
	int				fd;
	ssize_t			index;
	ssize_t			status;
	t_strlist		*strlist;
	struct s_fdlist	*prev;
	struct s_fdlist	*next;
}	t_fdlist;

#endif
