/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee2 <junlee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:58:22 by junlee2           #+#    #+#             */
/*   Updated: 2022/08/01 16:13:07 by junlee2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 100

typedef struct s_fdlist
{
	int				fd;
	char			buffer[BUFFER_SIZE];
	int				index;
	struct s_fdlist	*next;
}	t_fdlist;

typedef struct s_strlist
{
	char				buffer[BUFFER_SIZE];
	struct s_strlist	*next;
}	t_strlist;


#endif
