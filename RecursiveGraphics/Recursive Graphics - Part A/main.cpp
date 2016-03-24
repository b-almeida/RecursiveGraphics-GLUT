#include <GL/glut.h>

/*
 * Initializes background and grid.
 */
void init2D(float r, float g, float b)
{
	glClearColor(r, g, b, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 200.0);
}

/*
 * Recursive H-drawing function.
 * Input: x-centre, y-centre, edge length
 */
void drawPattern(float x, float y, float length)
{
	if (length >= 1)
	{
		// draw 3 lines
		glBegin(GL_LINES);
			glVertex2f( x - (length / 2), y );					// centre edge
			glVertex2f( x + (length / 2), y );

			glVertex2f( x - (length / 2), y - (length / 2) );	// left edge
			glVertex2f( x - (length / 2), y + (length / 2) );

			glVertex2f( x + (length / 2), y - (length / 2) );	// right edge
			glVertex2f( x + (length / 2), y + (length / 2) );
		glEnd();

		// recurse 4 times
		drawPattern( x - (length / 2), y - (length / 2), length / 2 );	// bottom left
		drawPattern( x - (length / 2), y + (length / 2), length / 2 );	// top left
		drawPattern( x + (length / 2), y - (length / 2), length / 2 );	// bottom right
		drawPattern( x + (length / 2), y + (length / 2), length / 2 );	// top right
	}
}

/*
 * Updates display.
 */
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawPattern(100.0, 100.0, 64.0);
	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Recursive H-Pattern");
	init2D(0.0, 0.0, 0.0);
	glutDisplayFunc(display);
	glutMainLoop();
}

