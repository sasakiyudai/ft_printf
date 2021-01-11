/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 09:45:58 by syudai            #+#    #+#             */
/*   Updated: 2020/11/26 00:19:08 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_this(char c, int len, t_per *p)
{
	if (len < 0)
		return ;
	while (len--)
	{
		write(1, &c, 1);
		p->cnt++;
	}
}

void	ft_per(t_per *p)
{
	p->real_cnt = 1;
	p->width = (p->width <= 1 ? 0 : p->width - 1);
	if (!p->flag[0] && !p->flag[1])
		put_this(' ', p->width, p);
	put_this('0', (!p->flag[0] && p->flag[1] ? p->width : 0), p);
	write(1, "%", 1);
	p->cnt++;
	if (p->flag[0])
		put_this(' ', p->width, p);
}

int		just_print(const char **start, const char **format)
{
	while (**format != '%' && **format)
		(*format)++;
	write(1, *start, *format - *start);
	return (*format - *start);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	const char	*start;
	int			cnt;

	cnt = 0;
	va_start(ap, format);
	if (format == NULL)
		cnt = -1;
	while (*format)
	{
		start = format;
		if (*start == '%')
			cnt += ft_percent(&start, &format, &ap);
		else
			cnt += just_print(&start, &format);
	}
	va_end(ap);
	return (cnt);
}
