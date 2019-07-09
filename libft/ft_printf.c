/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 03:16:31 by smoreno-          #+#    #+#             */
/*   Updated: 2019/04/29 03:16:37 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_resetspe(t_lst_args *spe)
{
	spe->flag = 0;
	spe->precision = 0;
	spe->base = 0;
	spe->width = 0;
	spe->negatif = 0;
	spe->len = 0;
	spe->i = 0;
	spe->j = 0;
	spe->err = 0;
	spe->plus = 0;
	spe->s_precision = 0;
	spe->save = 0.0;
	spe->value = 0.0;
	spe->padf = 0;
	spe->tmp = 0;
	spe->temp = 0;
	ft_bzero(spe->buf, (size_t)BUFFER_SIZE);
	ft_bzero(spe->str, 5);
}

void	ft_rpading(t_lst_args *spe)
{
	int i;

	i = 0;
	ft_print_lst(spe);
	if (spe->precision > 0)
		i = spe->width - spe->precision;
	else
		i = spe->width - spe->len;
	while (i-- > 0)
	{
		if (spe->flag & FLAG_ZEROPAD && !(spe->flag & FLAG_LEFT))
			ft_putchar('0');
		else
			ft_putchar(' ');
		spe->count_print++;
	}
	spe->width = 0;
}

int		loopformat(t_lst_args *spe, const char **format, va_list va)
{
	while (**format && match_char(VALID_SPEFLAG, **format)
			&& spe->swi != 1)
	{
		ft_get_flags(format, spe, va);
		if (**format == 's' || **format == 'S' || **format == 'c'
				|| **format == 'p' || **format == '%' || **format == 'C')
		{
			if (ft_print_char(format, spe, va) == -1)
				return (-1);
		}
		else if (match_char(VALID_NBOP, **format) == 1)
		{
			get_base(format, spe, va);
			spe->swi = 1;
		}
	}
	return (0);
}

void	ft_parce(t_lst_args *spe, const char **format, va_list va)
{
	while (**format)
	{
		if (**format != '%' && (spe->width--))
		{
			if (!(spe->flag & FLAG_LEFT) && (spe->width > 0))
				ft_rpading(spe);
			ft_lst_link(**format, spe);
			(*format)++;
			if ((spe->flag & FLAG_LEFT))
				ft_rpading(spe);
		}
		if (**format == '%' && (*format)++)
		{
			ft_resetspe(spe);
			if (loopformat(spe, format, va) == -1)
			{
				ft_free_lst(spe);
				break ;
			}
		}
		if (**format != '\0')
			spe->swi = 0;
		if (**format == '\0')
			ft_print_lst(spe);
	}
}

int		ft_printf(const char *format, ...)
{
	t_lst_args		*spe;
	va_list			va;
	int				ret;

	spe = NULL;
	if ((spe = (t_lst_args *)malloc(sizeof(t_lst_args))) == NULL)
		return (-1);
	ft_bzero(spe, sizeof(t_lst_args));
	spe->len = (int)ft_strlen(format);
	va_start(va, format);
	ft_parce(spe, &format, va);
	va_end(va);
	ret = (spe->err == -1) ? -1 : spe->count_print;
	free(spe);
	return (ret);
}
