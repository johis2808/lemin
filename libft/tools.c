/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <smoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 02:59:58 by smoreno-          #+#    #+#             */
/*   Updated: 2019/04/29 03:13:14 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_buffzerop(t_lst_args *spe)
{
	if (spe->width && (spe->flag & FLAG_ZEROPAD)
			&& (spe->flag & (FLAG_PLUS | FLAG_SPACE)))
		spe->width--;
	else if (spe->negatif == 1 && (spe->flag & FLAG_ZEROPAD))
		spe->width--;
	while (spe->len < spe->precision && (spe->len < BUFFER_SIZE))
		spe->buf[spe->len++] = '0';
	if ((spe->flag & FLAG_ZEROPAD) && (spe->flag & FLAG_HASH))
	{
		spe->width = spe->width - spe->len;
		if (spe->base == 8 || spe->base == 16)
			ft_buffzerohach(spe);
	}
	while ((spe->flag & FLAG_ZEROPAD) && (spe->width > 0)
		&& (spe->len < spe->width) && (spe->len < BUFFER_SIZE))
		spe->buf[spe->len++] = '0';
	if ((spe->flag & FLAG_ZEROPAD) && (((int)ft_strlen(spe->buf)
		>= spe->width) || ((int)ft_strlen(spe->buf) >= spe->precision)))
	{
		spe->flag &= ~FLAG_ZEROPAD;
		spe->width = 0;
	}
}

void	ft_buffhash(t_lst_args *spe)
{
	if ((spe->base == 16) && !(spe->flag & FLAG_UPPERCASE)
			&& (spe->len < BUFFER_SIZE))
		spe->buf[spe->len++] = 'x';
	else if ((spe->base == 16) && (spe->flag & FLAG_UPPERCASE)
			&& (spe->len < BUFFER_SIZE))
		spe->buf[spe->len++] = 'X';
	else if ((spe->base == 2) && (spe->len < BUFFER_SIZE))
		spe->buf[spe->len++] = 'b';
	if (((spe->len < BUFFER_SIZE) && (spe->precision < spe->len
	|| spe->precision == 0)) || (spe->buf[spe->len - 1] != '0'))
		spe->buf[spe->len++] = '0';
	spe->buf[spe->len] = '\0';
}

void	padnvalue(t_lst_args *spe)
{
	if (spe->width != 0)
		spe->len = spe->width -= 3;
	if (spe->precision != 0)
		spe->len = spe->precision;
	while (spe->len--)
	{
		ft_putchar('0');
		spe->count_print++;
	}
	spe->width = 0;
}

void	ptrnvalue(t_lst_args *spe)
{
	ft_print_lst(spe);
	if (!(spe->flag & FLAG_LEFT) && !(spe->flag & FLAG_ZEROPAD)
	&& (spe->width > 3) && (spe->width -= 3))
		ft_rpading(spe);
	spe->count_print += 2;
	ft_putstr("0x");
	if (!(spe->flag & FLAG_LEFT) && !(spe->flag & FLAG_ZEROPAD)
	&& !(spe->flag & FLAG_PRECISION))
	{
		ft_putchar('0');
		spe->count_print++;
	}
	if (spe->width > 2 && (spe->count_print++))
		ft_putchar('0');
	if (((spe->flag & FLAG_ZEROPAD) && (spe->width != 0))
	|| ((spe->flag & FLAG_PRECISION) && (spe->precision != 0)))
		padnvalue(spe);
	if ((spe->flag & FLAG_LEFT) && !(spe->flag & FLAG_ZEROPAD)
	&& (spe->width != 0))
	{
		spe->width -= 3;
		ft_rpading(spe);
	}
}

void	ft_printpad(t_lst_args *spe)
{
	int		i;

	ft_print_lst(spe);
	if (!(spe->flag & FLAG_LEFT) && spe->width > 0
	&& spe->width > spe->precision)
	{
		i = spe->width - spe->precision;
		while (i-- > 0)
		{
			if (spe->flag & FLAG_ZEROPAD)
				ft_putchar('0');
			else if (!(spe->flag & FLAG_ZEROPAD))
				ft_putchar(' ');
			spe->count_print++;
		}
		spe->width = 0;
	}
}
