/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numb_convert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 21:00:06 by smoreno-          #+#    #+#             */
/*   Updated: 2019/04/29 03:12:02 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nbrlong(t_lst_args *spe, va_list va)
{
	int					ret;
	unsigned long long	value;

	ret = 0;
	if (spe->flag & FLAG_LONGLONG)
	{
		ret = ft_long_long(spe, va_arg(va, unsigned long long));
	}
	else if (spe->flag & FLAG_LONG)
		ret = ft_long_long(spe, va_arg(va, unsigned long));
	else
	{
		if (spe->flag & FLAG_CHAR)
			value = (unsigned char)va_arg(va, unsigned int);
		else if (spe->flag & FLAG_SHORT)
			value = (unsigned short int)va_arg(va, unsigned int);
		else
			value = va_arg(va, unsigned int);
		ret = ft_long_long(spe, value);
	}
	return (ret);
}

int		ft_getintarglong(t_lst_args *spe, va_list va)
{
	long long value;

	if (spe->flag & FLAG_LONGLONG)
	{
		value = va_arg(va, long long);
		spe->negatif = ((value < 0) ? 1 : 0);
		value = (value < 0) ? value * -1 : value;
		return (ft_long_long(spe, (unsigned long long)value));
	}
	else if (spe->flag & FLAG_LONG)
	{
		value = va_arg(va, long);
		spe->negatif = ((value < 0) ? 1 : 0);
		value = (value < 0) ? value * -1 : value;
		return (ft_long_long(spe, (unsigned long long)value));
	}
	return (-1);
}

int		ft_get_intarg(t_lst_args *spe, va_list va)
{
	long long value;

	if (spe->flag & FLAG_LONGLONG || spe->flag & FLAG_LONG)
		return (ft_getintarglong(spe, va));
	else
	{
		if (spe->flag & FLAG_CHAR)
			value = (char)va_arg(va, int);
		else if (spe->flag & FLAG_SHORT)
			value = (short int)va_arg(va, int);
		else
			value = va_arg(va, int);
		spe->negatif = ((value < 0) ? 1 : 0);
		value = (value < 0) ? value * -1 : value;
		return (ft_long_long(spe, (unsigned long long)value));
	}
}

int		ft_uvalue(const char **format, t_lst_args *spe, va_list va)
{
	unsigned long long	value;
	long long			value2;
	int					ret;

	ret = 0;
	value = 0;
	value2 = 0;
	if (**format == 'U')
	{
		value = va_arg(va, long);
		ft_long_long(spe, (unsigned long long)value);
	}
	else
	{
		value2 = va_arg(va, long);
		spe->negatif = ((value2 < 0) ? 1 : 0);
		value2 = (value2 < 0) ? value2 * -1 : value2;
		ret = ft_long_long(spe, (unsigned long long)value2);
	}
	return (ret);
}

int		ft_nbr(const char **format, t_lst_args *spe, va_list va)
{
	int ret;

	if (!(spe->flag & FLAG_WILD) && spe->width == 0)
		ret = 0;
	if ((**format != 'i') && (**format != 'd') && (**format != 'D'))
		spe->flag &= ~(FLAG_PLUS | FLAG_SPACE);
	if ((spe->flag & FLAG_PRECISION && spe->precision != 0)
	|| (((spe->flag & FLAG_PRECISION) && (spe->flag & FLAG_ZEROPAD))
	&& (spe->precision == 0)))
		spe->flag &= ~FLAG_ZEROPAD;
	if ((spe->flag & FLAG_WILD) && (spe->flag & FLAG_PRECISION))
		spe->flag |= FLAG_ZEROPAD;
	if ((**format == 'i') || (**format == 'd'))
		ret = ft_get_intarg(spe, va);
	else if (**format == 'U' || **format == 'D')
		ret = ft_uvalue(format, spe, va);
	else if (**format == 'f' || **format == 'F')
		ret = ft_float(spe, va);
	else
		ret = ft_nbrlong(spe, va);
	(*format)++;
	return (ret);
}
