/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 03:15:07 by smoreno-          #+#    #+#             */
/*   Updated: 2019/04/29 03:15:11 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_speflag2(const char **format, t_lst_args *spe)
{
	if (**format == '#')
	{
		spe->flag |= FLAG_HASH;
		(*format)++;
		return (0);
	}
	if (**format == ' ')
	{
		spe->flag |= FLAG_SPACE;
		(*format)++;
		return (0);
	}
	return (-1);
}

int				get_speflag(const char **format, t_lst_args *spe)
{
	if (**format == '+')
	{
		spe->flag |= FLAG_PLUS;
		(*format)++;
		return (0);
	}
	if (**format == '-')
	{
		spe->flag |= FLAG_LEFT;
		(*format)++;
		return (0);
	}
	if (**format == '0')
	{
		spe->flag |= FLAG_ZEROPAD;
		(*format)++;
		return (0);
	}
	if (**format == '#' || **format == ' ')
		return (get_speflag2(format, spe));
	return (-1);
}

static int		ft_get_otherlength_modif(const char **format, t_lst_args *spe)
{
	if (**format == 'j')
	{
		spe->flag |= (sizeof(intmax_t) == sizeof(long)
				? FLAG_LONG : FLAG_LONGLONG);
		(*format)++;
		return (0);
	}
	if (**format == 'z')
	{
		spe->flag |= (sizeof(size_t) == sizeof(long)
				? FLAG_LONG : FLAG_LONGLONG);
		(*format)++;
		return (0);
	}
	return (-1);
}

static int		ft_get_length_modifiers(const char **format, t_lst_args *spe)
{
	if (**format == 'l')
	{
		spe->flag |= FLAG_LONG;
		(*format)++;
		if (**format == 'l')
		{
			spe->flag |= FLAG_LONGLONG;
			(*format)++;
		}
		return (0);
	}
	if (**format == 'h')
	{
		spe->flag |= FLAG_SHORT;
		(*format)++;
		if (**format == 'h')
		{
			spe->flag |= FLAG_CHAR;
			(*format)++;
		}
		return (0);
	}
	else if ((**format == 'j' || **format == 'z'))
		return (ft_get_otherlength_modif(format, spe));
	return (-1);
}

int				ft_get_flags(const char **format, t_lst_args *spe, va_list va)
{
	int		i;

	i = 0;
	while (get_speflag(format, spe) != -1)
		;
	if ((**format >= '0') && (**format <= '9'))
	{
		spe->width = ft_atoi(*format);
		spe->intlen = ft_intlen(spe->width);
		while (i++ < spe->intlen)
			(*format)++;
	}
	if (**format == '*')
		get_wild(format, spe, va);
	if (**format == '.')
		return (get_precision(format, spe, va));
	return (ft_get_length_modifiers(format, spe));
}
