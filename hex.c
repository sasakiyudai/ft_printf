/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 23:55:06 by syudai            #+#    #+#             */
/*   Updated: 2020/11/26 00:35:49 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_putnbr_u_fd(unsigned long long n, t_per *p, int fd)
{
	if (n < 0)
		ft_putnbr_u_fd(-n, p, fd);
	else if (n < 10)
		write_digit(n, p, fd);
	else
	{
		ft_putnbr_u_fd(n / 10, p, fd);
		ft_putnbr_u_fd(n % 10, p, fd);
	}
}

void			write_hex_digit(int n, t_per *p, int fd)
{
	char		c;
	const char	*x;
	const char	*large;

	x = "0123456789abcdef";
	large = "0123456789ABCDEF";
	if (p->type == 6)
		c = x[n];
	else
		c = large[n];
	write(fd, &c, 1);
	p->cnt++;
}

void			ft_putnbr_hex_fd(unsigned long long n, t_per *p, int fd)
{
	if (n < 0)
		ft_putnbr_hex_fd(-n, p, fd);
	else if (n < 16)
		write_hex_digit(n, p, fd);
	else
	{
		ft_putnbr_hex_fd(n / 16, p, fd);
		ft_putnbr_hex_fd(n % 16, p, fd);
	}
}

void			ft_uint(va_list *ap, t_per *p)
{
	unsigned long long num;

	num = (unsigned int)va_arg(*ap, int);
	ft_set(0, num, p);
	if (!p->flag[0] && !p->flag[1])
		put_this(' ', p->width, p);
	put_this('0', p->precision +
		(!p->flag[0] && p->flag[1] ? p->width : 0), p);
	if (num && p->type == 5)
		ft_putnbr_u_fd(num, p, 1);
	else if (num)
		ft_putnbr_hex_fd(num, p, 1);
	if (p->flag[0])
		put_this(' ', p->width, p);
}

void			ft_ptr(va_list *ap, t_per *p)
{
	unsigned long long num;

	p->type = 6;
	if ((num = (unsigned long long)va_arg(*ap, void *)) == 0)
	{
		p->precision = (p->precision == -1 ? 1 : p->precision);
		p->real_cnt = 2 + p->precision;
		p->width = (p->width <= p->real_cnt ? 0 : p->width - p->real_cnt);
	}
	else
		ft_set(1, num, p);
	if (!p->flag[0] && !p->flag[1])
		put_this(' ', p->width, p);
	write(1, "0x", 2);
	p->cnt += 2;
	put_this('0', p->precision +
		(!p->flag[0] && p->flag[1] ? p->width : 0), p);
	if (num)
		ft_putnbr_hex_fd(num, p, 1);
	if (p->flag[0])
		put_this(' ', p->width, p);
}
