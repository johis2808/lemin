/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 03:16:05 by smoreno-          #+#    #+#             */
/*   Updated: 2019/04/29 03:16:10 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_buffpading(t_lst_args *spe, int i)
{
	ft_print_lst(spe);
	if (!(spe->flag & FLAG_LEFT) && !(spe->flag & FLAG_ZEROPAD)
		&& (spe->width != 0 || spe->precision != 0))
	{
		i = ((spe->precision > spe->len) ? spe->precision : spe->len);
		while (i++ < spe->width)
		{
			ft_putchar(' ');
			spe->count_print++;
		}
		spe->width = 0;
	}
	ft_printbuff(spe);
	if ((spe->flag & FLAG_LEFT) || (spe->flag & FLAG_ZEROPAD))
	{
		spe->precision = ((spe->precision > spe->len)
		? spe->precision : spe->len);
		ft_rpading(spe);
	}
}

int		ft_buff_format(t_lst_args *spe)
{
	int i;

	i = 0;
	if (!(spe->flag & FLAG_LEFT) || (spe->len < spe->precision))
		ft_buffzerop(spe);
	if (spe->flag & FLAG_HASH)
		ft_buffhash(spe);
	if (spe->len < BUFFER_SIZE)
		ft_getsign(spe);
	if (spe->precision > spe->len)
	{
		i = spe->precision - spe->len;
		while (i--)
		{
			ft_putchar('0');
			spe->count_print++;
		}
		if (spe->precision > spe->width)
			spe->width = 0;
	}
	ft_buffpading(spe, i);
	return (spe->count_print);
}

void	ft_zeroval(t_lst_args *spe)
{
	ft_print_lst(spe);
	spe->width--;
	if (spe->flag & FLAG_PLUS)
	{
		spe->width--;
		if (!(spe->flag & FLAG_LEFT) && spe->width > 0
		&& !(spe->flag & FLAG_ZEROPAD))
			ft_rpading(spe);
		ft_putchar('+');
		if (!(spe->flag & FLAG_LEFT) && spe->width > 0
		&& (spe->flag & FLAG_ZEROPAD))
			ft_rpading(spe);
		spe->count_print++;
	}
	if ((spe->flag & FLAG_SPACE) && spe->negatif != 1
	&& !(spe->flag & FLAG_PLUS))
	{
		ft_putchar(' ');
		spe->width--;
		spe->count_print++;
	}
	if (!(spe->flag & FLAG_LEFT) && spe->width > 0)
		ft_rpading(spe);
	ft_putchar('0');
	spe->count_print++;
}

void	ft_itoabuff(t_lst_args *spe, unsigned long long value)
{
	char digit;

	while (value && (spe->len < BUFFER_SIZE))
	{
		digit = (char)(value % spe->base);
		if (digit < 10)
			spe->buf[spe->len++] = digit + '0';
		else
			spe->buf[spe->len++] = (spe->flag & FLAG_UPPERCASE
				? 'A' : 'a') + digit - 10;
		value /= spe->base;
	}
	spe->buf[spe->len] = '\0';
	spe->buflen = ft_strlen(spe->buf);
}

int		ft_long_long(t_lst_args *spe, unsigned long long value)
{
	if (spe->negatif < 0 || (!value && spe->base != 8))
		spe->flag &= ~FLAG_HASH;
	if (!(spe->flag & FLAG_PRECISION) || value)
	{
		if (value == 0)
		{
			ft_zeroval(spe);
			if (((spe->flag & FLAG_LEFT) || (spe->flag & FLAG_ZEROPAD))
			&& (spe->width > 0))
				ft_rpading(spe);
			return (0);
		}
	}
	ft_itoabuff(spe, value);
	return (ft_buff_format(spe));
}
