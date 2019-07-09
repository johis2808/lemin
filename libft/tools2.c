/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <smoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 23:25:34 by smoreno-          #+#    #+#             */
/*   Updated: 2019/04/29 03:13:39 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nulstring(const char **format, t_lst_args *spe, char *ptr)
{
	if (ptr == '\0' || (!ptr && !(spe->flag & FLAG_ZEROPAD)))
	{
		if (!(spe->flag & FLAG_ZEROPAD))
		{
			ft_print_lst(spe);
			if ((spe->flag & FLAG_PRECISION))
				spe->precision = (spe->precision == 0) ? 0 : spe->precision;
			else
				spe->precision = (spe->precision > 0) ? spe->precision : 6;
			if (!(spe->flag & FLAG_LEFT))
				ft_rpading(spe);
			write(1, "(null)", spe->precision);
			spe->count_print += spe->precision;
			if (spe->flag & FLAG_LEFT)
				ft_rpading(spe);
		}
	}
	spe->precision = ((spe->precision > spe->width) ? 0 : spe->precision);
	ft_rpading(spe);
	(*format)++;
	return (1);
}

int		ft_initstring(const char **format, t_lst_args *spe, va_list va)
{
	spe->ptr = va_arg(va, char*);
	if (spe->ptr == '\0' || (!spe->ptr && !(spe->flag & FLAG_ZEROPAD)))
	{
		if ((!(spe->flag & FLAG_LEFT) && !(spe->flag & FLAG_PRECISION))
		&& (spe->width > 6))
		{
			spe->precision = (spe->precision > 0) ? spe->precision : 6;
			ft_rpading(spe);
		}
		return (ft_nulstring(format, spe, spe->ptr));
	}
	spe->len = (unsigned int)ft_strlen((const char *)spe->ptr);
	if (spe->flag & FLAG_PRECISION && spe->precision > spe->len)
	{
		spe->precision = 0;
		spe->flag &= ~FLAG_PRECISION;
	}
	return (0);
}

int		ft_string(const char **format, t_lst_args *spe, va_list va)
{
	if (ft_initstring(format, spe, va) == 1)
		return (1);
	if (ft_pastring(format, spe, spe->ptr) == 1)
		return (1);
	else
	{
		spe->precision = spe->len;
		ft_printpad(spe);
	}
	if (**format == 's' && !(spe->flag & FLAG_LONG))
		ft_printwchar(spe->ptr, spe);
	if ((spe->flag & FLAG_LEFT) && (spe->flag & FLAG_ZEROPAD) && spe->width > 0)
	{
		spe->precision = spe->len + 1;
		ft_printpad(spe);
	}
	else if (((spe->flag & FLAG_LEFT) || (spe->flag & FLAG_ZEROPAD))
		&& (spe->width > spe->len))
		ft_rpading(spe);
	(*format)++;
	return (0);
}

int		ft_wstring(t_lst_args *spe, wchar_t *ptr)
{
	int		ret;
	int		i;

	ret = 0;
	i = spe->precision;
	if (spe->count_print > 0 && spe->err == -1)
		spe->count_print = 0;
	while (*ptr != '\0' && i > 0)
	{
		if (!(ret = ft_putw(ptr, spe)))
			i = 0;
		if (ret == -1)
			return (-1);
		spe->count_print += ret;
		if (spe->len > spe->precision)
			break ;
		i -= ret;
		ptr++;
	}
	if ((spe->flag & FLAG_LEFT) && (spe->width > spe->len))
		ft_rpading(spe);
	return (ret);
}

int		ft_pawchar(wchar_t c, t_lst_args *spe, const char **format)
{
	ft_print_lst(spe);
	if (c == 0)
	{
		spe->count_print++;
		ft_putchar('\0');
		(*format)++;
		return (1);
	}
	ft_pwchar(c, spe);
	if (ft_padwchar(spe, format) == 1)
		return (1);
	if (!(spe->flag & FLAG_LEFT))
		ft_rpading(spe);
	ft_printwchar(spe->str, spe);
	if ((spe->flag & FLAG_LEFT))
		ft_rpading(spe);
	return (0);
}
