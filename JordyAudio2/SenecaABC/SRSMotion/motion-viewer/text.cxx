/*
 *	text.c general definition file for displaying stroke font strings
 *
 *	AUTHOR:			O. Stroosma
 *	DATE:			17-2-99
 *	REVISION DATE:	17-2-99
 *
 */
#include <GL/glut.h>

/*
 *	strokeString - Stroke font string 
 */
void strokeString(int x, int y, const char *msg, void *font, double size)
{
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, size);
	while (*msg) {
		glutStrokeCharacter(font, *msg);
		msg++;
	}
	glPopMatrix();
}

