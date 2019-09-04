/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 03:15:27 by smoreno-          #+#    #+#             */
/*   Updated: 2019/04/29 03:15:41 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_float_part(t_lst_args *spe, long double value)
{
	int				i;

	if (spe->precision)
	{
		ft_putchar('.');
		spe->width--;
		spe->tmp++;
		spe->count_print++;
		while (spe->precision > 0)
		{
			value *= 10;
			i = (int)value;
			ft_putchar(i + '0');
			spe->count_print++;
			spe->width--;
			spe->precision--;
			value -= i;
		}
	}
}

void	ft_integerpad(t_lst_args *spe, unsigned long long len)
{
	if (!(spe->flag & FLAG_LEFT))
	{
		spe->tmp = spe->precision;
		spe->precision = spe->precision + len;
		--spe->width;
		ft_rpading(spe);
		spe->precision = spe->tmp;
	}
	else
		spe->tmp += spe->precision;
}

void	ft_integer_part(t_lst_args *spe, long double value)
{
	unsigned long long	i;
	unsigned long long	len;

	i = 20;
	len = 1;
	spe->save = value;
	while (i > 0 && spe->save > 10)
	{
		len *= 10;
		spe->save /= 10;
		i--;
		spe->tmp++;
	}
	ft_integerpad(spe, len);
	while (len > 0)
	{
		i = (int)(value / len);
		ft_putchar(i + '0');
		spe->width--;
		spe->count_print++;
		i *= len;
		value -= i;
		len /= 10;
	}
	ft_float_part(spe, value);
}

int		ft_divpadval(t_lst_args *spe)
{
	spe->i = 20;
	spe->len = (spe->value < 0) ? 1 : 0;
	spe->save = spe->value;
	spe->padf = spe->width;
	if (spe->value != spe->value)
		return (nanv(spe, spe->value));
	while (spe->i > 0 && spe->value > 10)
	{
		spe->len++;
		spe->value /= 10;
		spe->i--;
	}
	spe->plus = 0.5;
	if (!(spe->flag & FLAG_PRECISION))
		spe->precision = 6;
	spe->s_precision = spe->precision;
	if (spe->precision > 0)
		spe->len += spe->precision + 1;
	while (spe->s_precision > 0)
	{
		spe->plus = spe->plus / 10;
		spe->s_precision--;
	}
	return (0);
}

int		ft_float(t_lst_args *spe, va_list va)
{
	if (!(spe->flag & FLAG_LONGFLOAT))
		spe->value = va_arg(va, double);
	else
		spe->value = va_arg(va, long double);
	ft_print_lst(spe);
	if ((ft_divpadval(spe) != 0))
		return (spe->count_print);
	if (spe->save < 0 && (spe->width = spe->width - 1))
	{
		spe->save = -spe->save;
		spe->negatif = 1;
		ft_putchar('-');
		spe->tmp++;
		spe->count_print++;
	}
	spe->save += spe->plus;
	ft_integer_part(spe, spe->save);
	if ((spe->flag & FLAG_LEFT))
	{
		spe->tmp = (spe->negatif == 1) ? ++spe->tmp : spe->tmp;
		spe->precision += spe->tmp;
		spe->width = spe->padf;
		ft_rpading(spe);
	}
	return (spe->count_print);
}
