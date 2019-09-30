/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minignl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 07:10:55 by thberrid          #+#    #+#             */
/*   Updated: 2019/09/30 08:38:59 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			str_to_line(char *str, char **line, char target)
{
	int		length;
	int		line_length;
	char	*position;
	char	*new_line;

	if (str == NULL)
		return (0);
	position = NULL;
	if (target && (position = ft_strchr(str, target)))
		length = position - str;
	else
		length = ft_strlen(str);
	if (!length)
		return (0);
	line_length = 0;
	if (*line)
		line_length = ft_strlen(*line);
	if (!(new_line = ft_strnew(length + line_length)))
		return (-1);
	if (*line)
		ft_strcpy(new_line, *line);
	ft_strncpy(new_line + line_length, str, length);
	ft_memdel((void **)line);
	*line = new_line;
	return (position ? 1 : 0);
}

int			update_str(char **str)
{
	int		length;
	char	*rest;
	char	*position;

	if (*str == NULL)
		return (0);
	if ((position = ft_strchr(*str, '\n')))
		length = position - *str;
	else
		return (0);
	length = ft_strlen(*str) - length;
	rest = NULL;
	if (position)
	{
		rest = ft_strnew(length);
		ft_strncpy(rest, position + 1, length);
	}
	ft_memdel((void **)str);
	*str = rest;
	return (position ? 1 : 0);
}

int			clean_this(int retrn, char **line, char *str)
{
	if (retrn < 0)
	{
		ft_memdel((void **)line);
		ft_memdel((void **)&str);
		return (-1);
	}
	ft_memdel((void **)line);
	ft_memdel((void **)&str);
	return (0);
}

int			precheck_static(char **str, char **line)
{
	int		retrn;

	if (str_to_line(*str, line, '\n') < 0)
		return (-1);
	retrn = update_str(str);
	if (retrn < 0 || retrn > 0)
		return (retrn);
	return (retrn);
}

int			minignl(const int fd, char **line)
{
	static char	*str;
	char		buffer[BUFF_SIZE + 1];
	int			retrn;

	if (fd < 0 || !line || read(fd, 0, 0) < 0 || BUFF_SIZE < 1)
		return (-1);
	*line = NULL;
	if (str != NULL && ft_strchr(str, '\n'))
	{
		retrn = precheck_static(&str, line);
		if (retrn > 0 || retrn < 0)
			return (retrn);
	}
	while ((retrn = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[retrn] = '\0';
		if ((retrn = str_to_line(buffer, &str, 0)) < 0)
			return (-1);
		if (ft_strchr(str, '\n') && str_to_line(str, line, '\n') < 0)
			return (-1);
		retrn = update_str(&str);
		if (retrn < 0 || retrn > 0)
			return (retrn);
	}
	return (clean_this(retrn, line, str));
}
