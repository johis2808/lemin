/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <smoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 06:15:17 by smoreno-          #+#    #+#             */
/*   Updated: 2019/04/29 03:12:50 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_parsechar(const char **format, t_lst_args *spe, va_list va)
{
	unsigned char	c;
	wchar_t			wc;

	if (**format == 'c' && !(spe->flag & FLAG_LONG))
	{
		spe->len = 1;
		if (!(spe->flag & FLAG_LEFT))
			ft_rpading(spe);
		c = (char)va_arg(va, int);
		ft_print_lst(spe);
		ft_putchar(c);
		spe->count_print++;
		if ((spe->flag & FLAG_LEFT) && !(spe->flag & FLAG_ZEROPAD))
			ft_rpading(spe);
	}
	if (**format == 'C' || (**format == 'c' && (spe->flag & FLAG_LONG)))
	{
		wc = va_arg(va, wchar_t);
		if (ft_testmaxw(format, spe, wc) == -1)
			return (-1);
		if (ft_pawchar(wc, spe, format) == 1)
			return (1);
	}
	(*format)++;
	return (1);
}

int		ft_pastring(const char **format, t_lst_args *spe, char *ptr)
{
	if ((spe->flag & FLAG_PRECISION) || spe->precision != 0)
	{
		ft_printpad(spe);
		if (**format == 's' && !(spe->flag & FLAG_LONG))
			ft_printwchar(spe->ptr, spe);
		else if (**format == 'S' || (**format == 's'
			&& (spe->flag & FLAG_LONG)))
			return (ft_wstring(spe, (wchar_t *)ptr));
		if ((spe->flag & FLAG_LEFT) && (spe->flag & FLAG_ZEROPAD)
			&& spe->width > 0)
		{
			spe->precision = spe->len + 1;
			ft_printpad(spe);
		}
		if (((spe->flag & FLAG_LEFT) || (spe->flag & FLAG_ZEROPAD))
			&& (spe->width > spe->len))
			ft_rpading(spe);
		(*format)++;
		return (1);
	}
	return (0);
}

int		ft_getptr(const char **format, t_lst_args *spe, va_list va)
{
	unsigned long long value;

	if (**format == 'p')
	{
		spe->flag |= FLAG_HASH;
		spe->flag &= ~FLAG_PLUS;
		spe->flag &= ~FLAG_SPACE;
		value = (unsigned long long)va_arg(va, void*);
		if (!value)
		{
			ptrnvalue(spe);
			(*format)++;
			return (0);
		}
		spe->base = 16;
		ft_long_long(spe, value);
		(*format)++;
		return (1);
	}
	return (0);
}

int		ft_percent(const char **format, t_lst_args *spe)
{
	(*format)++;
	spe->len = 1;
	if (spe->flag & FLAG_PRECISION && spe->precision < spe->width)
		spe->precision = 0;
	if (!(spe->flag & FLAG_LEFT))
		ft_rpading(spe);
	ft_print_lst(spe);
	ft_putchar('%');
	spe->count_print++;
	ft_rpading(spe);
	return (1);
}

int		ft_print_char(const char **format, t_lst_args *spe, va_list va)
{
	wchar_t		*ptr;

	spe->swi = 1;
	ptr = 0;
	if (**format == 'C' || **format == 'c')
		return (ft_parsechar(format, spe, va));
	if (**format == 's' && !(spe->flag & FLAG_LONG))
		if (ft_string(format, spe, va) == 0)
			return (1);
	if (**format == 'S' || (**format == 's' && (spe->flag & FLAG_LONG)))
	{
		ptr = va_arg(va, wchar_t *);
		if (ptr == '\0' || *ptr == '\0')
			return (ft_nulstring(format, spe, (char*)ptr));
		spe->len = (unsigned int)ft_wlen(ptr, spe);
		ft_pastring(format, spe, (char *)ptr);
		(*format)++;
		return (1);
	}
	if (**format == '%')
		return (ft_percent(format, spe));
	if (**format == 'p')
		return (ft_getptr(format, spe, va));
	return (0);
}
