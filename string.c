/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 23:50:39 by syudai            #+#    #+#             */
/*   Updated: 2020/11/26 18:07:32 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_char(va_list *ap, t_per *p)
{
	char c;

	c = (char)va_arg(*ap, int);
	p->real_cnt = 1;
	p->precision = 1;
	p->width = p->width <= p->real_cnt ? 0 : p->width - p->real_cnt;
	if (!p->flag[0])
		put_this(' ', p->width, p);
	write(1, &c, 1);
	p->cnt++;
	if (p->flag[0])
		put_this(' ', p->width, p);
}

int			ft_null(t_per *p, int apisnull)
{
	if (!apisnull)
	{
		p->s = "(null)";
		p->real_cnt = 6;
		if (p->real_cnt > p->precision)
			p->real_cnt = p->precision;
	}
	return (0);
}

int			ft_strlen(char *s)
{
	int i;

	i = 0;
	while ((s[i]))
		i++;
	return (i);
}

int			ft_set_s(va_list *ap, t_per *p)
{
	int n;

	n = 0;
	if (ap == NULL)
		return (ft_null(p, 1));
	if ((p->s = va_arg(*ap, char *)) == NULL)
		return (ft_null(p, 0));
	while (n < p->precision && n < ft_strlen(p->s))
		n++;
	p->real_cnt = n;
	return (n);
}

void		ft_str(va_list *ap, t_per *p)
{
	if (p->precision == -1)
		p->precision = INT_MAX;
	ft_set_s(ap, p);
	p->width = p->width >= p->real_cnt ? p->width - p->real_cnt : 0;
	if (!p->flag[0])
		put_this((p->flag[1]) ? '0' : ' ', p->width, p);
	write(1, p->s, p->real_cnt);
	p->cnt += p->real_cnt;
	if (p->flag[0])
		put_this(' ', p->width, p);
}
