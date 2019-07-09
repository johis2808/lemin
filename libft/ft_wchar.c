/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:58:19 by smoreno-          #+#    #+#             */
/*   Updated: 2019/04/29 03:17:13 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_wlen(wchar_t *str, t_lst_args *spe)
{
	spe->j = 0;
	spe->i = 0;
	if (spe->flag & FLAG_PRECISION)
	{
		while (str[spe->i] != '\0' && spe->j < spe->precision)
		{
			if (ft_loopwlen(str, spe) == 0)
				break ;
			spe->i++;
		}
	}
	else
		ft_loopwlen2(str, spe);
	spe->precision = spe->j;
	return (spe->j);
}

int		ft_putw(wchar_t *w, t_lst_args *spe)
{
	if (spe->width == 0 && ft_loopcheckvalidw(w, spe) == -1)
		return (-1);
	else
	{
		ft_print_lst(spe);
		ft_pwchar(*w, spe);
		write(1, spe->str, spe->len);
		return (spe->len);
	}
}

int		ft_loopcheckvalidw(wchar_t *w, t_lst_args *spe)
{
	spe->i = 0;
	while (spe->i < 5 && w[spe->i] != '\0')
	{
		if (w[spe->i] < 0 || (w[spe->i] >= 0xD800
		&& w[spe->i] < 0xE000) || w[spe->i] > 0x10FFFF)
		{
			spe->err = -1;
			return (-1);
		}
		spe->i++;
	}
	return (0);
}

int		ft_pwchar(wchar_t c, t_lst_args *spe)
{
	ft_bzero(spe->str, 5);
	if (c <= 0x7F)
		spe->str[0] = (unsigned char)c;
	else if (c <= 0x7FF)
	{
		spe->str[0] = (c >> 6) | 0xC0;
		spe->str[1] = (c & 0x3F) | 0x80;
	}
	else if (c <= 0xFFFF)
	{
		spe->str[0] = (c >> 12) | 0xE0;
		spe->str[1] = (c >> 6 & 0x3F) | 0x80;
		spe->str[2] = (c & 0x3F) | 0x80;
	}
	else if (c <= 0x10FFFF)
	{
		spe->str[0] = (c >> 18) | 0xF0;
		spe->str[1] = (c >> 12 & 0x3F) | 0x80;
		spe->str[2] = (c >> 6 & 0x3F) | 0x80;
		spe->str[3] = (c & 0x3F) | 0x80;
	}
	spe->len = (unsigned int)ft_strlen((const char *)spe->str);
	if (spe->len == 0)
		return (-1);
	return (0);
}

void	ft_printwchar(char *str, t_lst_args *spe)
{
	ft_print_lst(spe);
	if (spe->flag & FLAG_PRECISION)
	{
		write(1, str, spe->precision);
		spe->count_print += spe->precision;
	}
	else
	{
		write(1, str, ft_strlen(str));
		spe->count_print += ft_strlen(str);
	}
}
