/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:02:44 by syudai            #+#    #+#             */
/*   Updated: 2020/11/26 00:35:34 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>

typedef struct	s_per
{
	int			flag[2];
	int			width;
	int			precision;
	int			type;
	int			real_cnt;
	int			cnt;
	char		*s;
}				t_per;

int				ft_printf(const char *format, ...);
int				just_print(const char **start, const char **format);
void			ft_per(t_per *p);
void			put_this(char c, int len, t_per *p);
void			ft_ptr(va_list *ap, t_per *p);
void			ft_uint(va_list *ap, t_per *p);
void			ft_putnbr_hex_fd(unsigned long long n, t_per *p, int fd);
void			write_hex_digit(int n, t_per *p, int fd);
void			ft_putnbr_u_fd(unsigned long long n, t_per *p, int fd);
void			ft_int(va_list *ap, t_per *p);
void			ft_putnbr_fd(long long n, t_per *p, int fd);
void			ft_int_set(long long num, t_per *p);
void			ft_set(long long num, unsigned long long unum,
t_per *p);
void			ft_u_set(long long isp, unsigned long long num, t_per *p);
int				ft_percent(const char **start, const char **format,
va_list *ap);
int				ft_search(char *s, char c);
void			the_print(const char **start, const char **format,
va_list *ap, t_per *p);
int				s_to_num(const char **format, va_list *ap, t_per *p, int isp);
void			ft_initialize(t_per *p);
void			ft_str(va_list *ap, t_per *p);
int				ft_set_s(va_list *ap, t_per *p);
int				ft_strlen(char *s);
int				ft_null(t_per *p, int apisnull);
void			ft_char(va_list *ap, t_per *p);
int				get_digit_hex(unsigned long long num);
void			ft_no_type(const char **start, const char **format, t_per *p);
int				get_digit(long long num);
int				get_digit_u(unsigned long long num);
void			write_digit(int n, t_per *p, int fd);

#endif
