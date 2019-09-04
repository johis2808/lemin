/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <smoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 01:27:00 by smoreno-          #+#    #+#             */
/*   Updated: 2019/04/29 03:14:22 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	get_base(const char **format, t_lst_args *spe, va_list va)
{
	int		ret;

	ret = 0;
	if (**format == 'x' || **format == 'X')
	{
		if (**format == 'X')
			spe->flag |= FLAG_UPPERCASE;
		spe->base = 16;
	}
	else if (**format == 'o' || **format == 'O')
	{
		if (**format == 'O')
			spe->flag |= FLAG_LONGLONG;
		spe->base = 8;
	}
	else if (**format == 'b')
		spe->base = 2;
	else
	{
		spe->base = 10;
		spe->flag &= ~FLAG_HASH;
	}
	ret = ft_nbr(format, spe, va);
}

int		ft_padwchar(t_lst_args *spe, const char **format)
{
	if (spe->flag & FLAG_PRECISION && spe->precision > spe->len)
	{
		spe->precision = 0;
		spe->flag &= ~FLAG_PRECISION;
	}
	if ((spe->flag & FLAG_PRECISION)
			|| spe->precision != 0 || spe->precision > spe->len)
	{
		if (!(spe->flag & FLAG_LEFT)
				&& spe->width > 0 && spe->width > spe->precision)
			ft_rpading(spe);
		ft_printwchar(spe->str, spe);
		if ((spe->flag & FLAG_LEFT) && (spe->width > spe->len))
			ft_rpading(spe);
		(*format)++;
		return (1);
	}
	return (0);
}

int		ft_loopwlen(wchar_t *str, t_lst_args *spe)
{
	if (*str != '\0' && str[spe->i] <= 0x7F)
	{
		if (spe->j + 1 > spe->precision)
			return (0);
		++spe->j;
	}
	else if (*str != '\0' && str[spe->i] <= 0x7FF)
	{
		if (spe->j + 2 > spe->precision)
			return (0);
		spe->j += 2;
	}
	else if (*str != '\0' && str[spe->i] <= 0xFFFF)
	{
		if (spe->j + 3 > spe->precision)
			return (0);
		spe->j += 3;
	}
	else if (*str != '\0' && str[spe->i] <= 0x10FFFF)
	{
		if (spe->j + 4 > spe->precision)
			return (0);
		spe->j += 4;
	}
	return (-1);
}

void	ft_loopwlen2(wchar_t *str, t_lst_args *spe)
{
	while (str[spe->i])
	{
		if (str[spe->i] <= 0x7F)
			spe->j++;
		else if (str[spe->i] <= 0x7FF)
			spe->j += 2;
		else if (str[spe->i] <= 0xFFFF)
			spe->j += 3;
		else if (str[spe->i] <= 0x10FFFF)
			spe->j += 4;
		spe->i++;
	}
}

int		nanv(t_lst_args *spe, long double value)
{
	if (value != value)
	{
		ft_putchar('n');
		ft_putchar('a');
		ft_putchar('n');
		spe->count_print++;
		spe->width--;
		return (spe->count_print);
	}
	return (0);
}
