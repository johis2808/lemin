/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pading.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <smoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 01:27:00 by smoreno-          #+#    #+#             */
/*   Updated: 2019/04/29 03:12:35 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_buffzerohach(t_lst_args *spe)
{
	spe->i = 0;
	if (spe->buf[spe->len - 1] != '0' && spe->base == 8)
	{
		spe->buf[spe->len++] = '0';
		spe->width--;
	}
	if (spe->base == 16)
		spe->width -= 2;
	while (spe->i++ < spe->width)
		spe->buf[spe->len++] = '0';
	if (spe->base == 16)
		ft_buffhash(spe);
	spe->flag &= ~FLAG_ZEROPAD;
	spe->flag &= ~FLAG_HASH;
	spe->width = 0;
}

int		ft_testmaxw(const char **format, t_lst_args *spe, wchar_t wc)
{
	if (wc < 0 || (wc >= 0xD800 && wc < 0xE000) || wc > 0x10FFFF)
	{
		(*format)++;
		spe->err = -1;
		return (-1);
	}
	return (0);
}
