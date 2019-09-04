/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 03:54:28 by smoreno-          #+#    #+#             */
/*   Updated: 2019/06/10 03:54:32 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"


void	keyboardEvent(unsigned char c, int x, int y)
{
	(void)x;
	(void)y;
	if (c == 27)
		exit(0);
	else if (c == 115)
		sleep(5);
	if (c == 102)
		glutFullScreen();
	if (c == 120)
		glutReshapeWindow(WIDTH, HEIGHT);
}

void	render(void)
{
	//glClear(GL_COLOR_BUFFER_BIT);
//	glColor3f(1, 1, 1);
	//glBegin(GL_QUADS);
	//glEnd();
	//glutSwapBuffers();
//	glClearColor(1.0,0,0,1.0); // sélectionne la couleur noire (qui est celle par défaut)
//	glClear(GL_COLOR_BUFFER_BIT); // efface le frame buffer
	//glColor3f(1.0,1.0,0.0); //yellow color
   //glutSolidSphere(0.5,60,50);
	//glutWireSphere(5.0,5,5);
	//glPushMatrix();
	// glTranslatef(1,2,0);
//	glRotatef(10, 0, 0, 0.7);
	glColor3f(1.0,1.0,0.0);
	//glColor3ub(0,255,255);
	glutSolidSphere(0.5,60,50);
	//glutWireSphere(3,10,10);
	// glPopMatrix();
	glFlush();
	glPopMatrix();
}

int		setUpGlutAndArray(int ac, char **av)
{
	glutInit(&ac, av);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("LEM_IN");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glPushMatrix();
	glOrtho(0.0, 1.0, 0.0, 1.0, 0.0, 500);
	glutDisplayFunc(render);
	//glutDisplayFunc();
	//glutIdleFunc(update);
	glutKeyboardFunc(keyboardEvent);
	glutMainLoop();
	return (0);
}

int	main(int argc, char** argv)
{
	setUpGlutAndArray(argc, argv);
}
