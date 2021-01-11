/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsnother.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 23:59:55 by syudai            #+#    #+#             */
/*   Updated: 2020/11/26 00:36:16 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			write_digit(int n, t_per *p, int fd)
{
	char c;

	c = n + '0';
	write(fd, &c, 1);
	p->cnt++;
}

int				get_digit_u(unsigned long long num)
{
	int i;

	i = 1;
	while (10 <= num)
	{
		num /= 10;
		i++;
	}
	return (i);
}

int				get_digit(long long num)
{
	int i;

	i = 1;
	while (num <= -10 || 10 <= num)
	{
		num /= 10;
		i++;
	}
	return (i);
}

void			ft_no_type(const char **start, const char **format, t_per *p)
{
	p->width = 0;
	p->real_cnt = *format - *start;
	write(1, *start, p->real_cnt);
}

int				get_digit_hex(unsigned long long num)
{
	int i;

	i = 1;
	while (16 <= num)
	{
		num /= 16;
		i++;
	}
	return (i);
}
