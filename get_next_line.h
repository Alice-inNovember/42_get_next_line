/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee2 <junlee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:58:22 by junlee2           #+#    #+#             */
/*   Updated: 2022/08/04 18:00:20 by junlee2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 10

typedef struct s_strlist
{
	char				buffer[BUFFER_SIZE];
	struct s_strlist	*next;
}	t_strlist;

typedef struct s_fdlist
{
	int				fd;
	size_t			index;
	size_t			size;
	t_strlist		*strlist;
	struct s_fdlist	*next;
}	t_fdlist;

#endif
