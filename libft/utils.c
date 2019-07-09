/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <smoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 20:41:26 by smoreno-          #+#    #+#             */
/*   Updated: 2019/04/29 03:14:00 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		match_char(char *str, char c)
{
	if (IS_DIGIT(c))
		return (1);
	else
	{
		while (*str != '\0')
		{
			if (*str == c)
				return (1);
			str++;
		}
	}
	return (0);
}

int		get_precision(const char **format, t_lst_args *spe, va_list va)
{
	int arg_prec;

	spe->i = 0;
	if (**format == '.' && ((*format)++))
	{
		spe->flag |= FLAG_PRECISION;
		if (**format >= '0' && **format <= '9')
		{
			spe->precision = ft_atoi(*format);
			spe->intlen = ft_intlen(spe->precision);
			while (spe->i++ < spe->intlen)
				(*format)++;
		}
		else if (**format == '*' && ((*format)++))
		{
			spe->flag |= FLAG_WILD;
			arg_prec = (int)va_arg(va, int);
			if (**format == 's')
				spe->precision = arg_prec > 0 ? arg_prec : -arg_prec;
			else
				spe->precision = arg_prec > 0 ? arg_prec : 0;
		}
		return (0);
	}
	return (-1);
}

void	get_wild(const char **format, t_lst_args *spe, va_list va)
{
	int wid;

	wid = 0;
	spe->flag |= FLAG_WILD;
	if (**format == '*')
	{
		(*format)++;
		wid = va_arg(va, int);
		if (wid < 0)
		{
			spe->flag |= FLAG_LEFT;
			spe->width = -wid;
		}
		else
			spe->width = wid;
		ft_get_flags(format, spe, va);
	}
}

void	ft_getsign(t_lst_args *spe)
{
	if (spe->negatif)
		spe->buf[spe->len++] = '-';
	else if (spe->flag & FLAG_PLUS)
		spe->buf[spe->len++] = '+';
	else if (spe->flag & FLAG_SPACE)
		spe->buf[spe->len++] = ' ';
}

void	ft_printbuff(t_lst_args *spe)
{
	int		i;

	i = 0;
	while (i++ < spe->len)
	{
		ft_putchar(spe->buf[spe->len - i]);
		spe->count_print++;
	}
}
