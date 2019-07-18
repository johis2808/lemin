/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 10:28:29 by smoreno-          #+#    #+#             */
/*   Updated: 2019/06/13 10:30:29 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include "../lem_in.h"
# include "freeglut.h"
# include "gl.h"
# include "glu.h"
# include <stdlib.h>

# define SPEEDING	8
# define WIDTH		1000
# define HEIGHT		1500
# define WMIN		100

void	keyboardEvent(unsigned char c, int x, int y);
int		setUpGlutAndArray(int argc, char **argv);

#endif
