/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee2 <junlee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 13:32:22 by junlee2           #+#    #+#             */
/*   Updated: 2022/07/27 13:05:05 by junlee2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>

int	ft_printf(const char *str, ...);
int	ft_putstr_cnt(char *s);
int	ft_putptr_cnt(unsigned long long n);
int	ft_putnbr_cnt(int n);
int	ft_un_putnbr_cnt(unsigned int n);
int	ft_puthexupper_cnt(unsigned int n);
int	ft_puthexlower_cnt(unsigned int n);

#endif
