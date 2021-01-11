/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 23:47:05 by syudai            #+#    #+#             */
/*   Updated: 2020/11/26 18:05:18 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_initialize(t_per *p)
{
	p->flag[0] = 0;
	p->flag[1] = 0;
	p->width = -1;
	p->precision = -1;
	p->type = -1;
	p->real_cnt = 0;
	p->cnt = 0;
	p->s = NULL;
}

int		s_to_num(const char **format, va_list *ap, t_per *p, int isp)
{
	int num;

	num = -1;
	if (**format == '*')
	{
		num = va_arg(*ap, int);
		if (num < 0 && !isp)
		{
			num *= -1;
			p->flag[0] = 1;
		}
		else if (num < 0)
			num = -1;
		(*format)++;
	}
	else if (isp || ('0' <= **format && **format <= '9'))
	{
		num = 0;
		while ('0' <= **format && **format <= '9')
		{
			num = num * 10 + (**format - '0');
			(*format)++;
		}
	}
	return (num);
}

void	the_print(const char **start, const char **format,
va_list *ap, t_per *p)
{
	if (p->type == -1)
	{
		ft_no_type(start, format, p);
		return ;
	}
	(*format)++;
	if (p->type == 8)
		ft_per(p);
	else if (5 <= p->type && p->type <= 7)
		ft_uint(ap, p);
	else if (p->type == 3 || p->type == 4)
		ft_int(ap, p);
	else if (p->type == 2)
		ft_ptr(ap, p);
	else if (p->type == 1)
		ft_str(ap, p);
	else
		ft_char(ap, p);
}

int		ft_search(char *s, char c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (i);
		i++;
	}
	return (-1);
}

int		ft_percent(const char **start, const char **format, va_list *ap)
{
	int		n;
	t_per	p;

	(*format)++;
	ft_initialize(&p);
	while ((n = ft_search("-0", **format)) >= 0)
	{
		p.flag[n] = 1;
		(*format)++;
	}
	p.width = s_to_num(format, ap, &p, 0);
	if (**format == '.')
	{
		(*format)++;
		p.precision = s_to_num(format, ap, &p, 1);
	}
	p.type = ft_search("cspdiuxX%", **format);
	the_print(start, format, ap, &p);
	return (p.cnt);
}
