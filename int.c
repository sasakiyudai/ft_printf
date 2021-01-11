/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 23:57:38 by syudai            #+#    #+#             */
/*   Updated: 2020/11/26 00:27:17 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_u_set(long long isp, unsigned long long num, t_per *p)
{
	int both_is;

	both_is = 0;
	if (p->width != -1 && p->precision != -1)
		both_is = 1;
	if (num == 0 && p->precision == 0)
		p->precision = 0;
	else if (num == 0)
		p->precision = p->precision >= 1 ? p->precision : 1;
	else
	{
		p->precision = p->precision <= p->real_cnt ?
			num == 0 && p->precision : p->precision - p->real_cnt;
	}
	p->width = p->width - p->real_cnt;
	if (both_is)
	{
		if (num != 0)
			p->width -= p->precision;
		else
			p->width += p->real_cnt - p->precision;
	}
	if (isp)
		p->width -= 2;
}

void			ft_set(long long num, unsigned long long unum, t_per *p)
{
	p->flag[1] = p->flag[1] && p->precision == -1;
	if (5 <= p->type && p->type <= 7)
	{
		if (p->type == 5)
			p->real_cnt = get_digit_u(unum);
		else
			p->real_cnt = get_digit_hex(unum);
		ft_u_set(num, unum, p);
	}
	else if (p->type == 3 || p->type == 4)
		ft_int_set(num, p);
}

void			ft_int_set(long long num, t_per *p)
{
	int both_is;

	both_is = 0;
	if (p->width != -1 && p->precision != -1)
		both_is = 1;
	p->real_cnt = get_digit(num);
	if (num == 0 && p->precision == 0)
		p->precision = 0;
	else if (num == 0)
		p->precision = p->precision >= 1 ? p->precision : 1;
	else
	{
		p->precision = p->precision <= p->real_cnt ?
			num == 0 && p->precision : p->precision - p->real_cnt;
	}
	p->width = p->width - p->real_cnt;
	if (both_is)
	{
		if (num != 0)
			p->width -= p->precision;
		else
			p->width += p->real_cnt - p->precision;
	}
	if (num < 0)
		p->width -= 1;
}

void			ft_putnbr_fd(long long n, t_per *p, int fd)
{
	if (n < 0)
		ft_putnbr_fd(-n, p, fd);
	else if (n < 10)
		write_digit(n, p, fd);
	else
	{
		ft_putnbr_fd(n / 10, p, fd);
		ft_putnbr_fd(n % 10, p, fd);
	}
}

void			ft_int(va_list *ap, t_per *p)
{
	long long num;

	num = va_arg(*ap, int);
	ft_set(num, 0, p);
	if (!p->flag[0] && !p->flag[1])
		put_this(' ', p->width, p);
	if (num < 0)
	{
		write(1, "-", 1);
		p->cnt++;
	}
	put_this('0', p->precision +
		(!p->flag[0] && p->flag[1] ? p->width : 0), p);
	if (num)
		ft_putnbr_fd(num, p, 1);
	if (p->flag[0])
		put_this(' ', p->width, p);
}
