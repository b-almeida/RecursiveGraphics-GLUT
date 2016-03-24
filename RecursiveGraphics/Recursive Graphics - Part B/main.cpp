/*
 NOTE: Choose pattern in display() function
 */

#include <GL/glut.h>
#include <cmath>

const float PI = 3.1415926535897932;	// for degrees to radians conversion

/*
 * Calculates sin of an angle in degrees.
 */
float sinD(float angle)
{
	return sin(angle * PI / 180);
}

/*
 * Calculates cos of an angle in degrees.
 */
float cosD(float angle)
{
	return cos(angle * PI / 180);
}

/*
 * Initializes background and grid.
 */
void init2D(float r, float g, float b)
{
	glClearColor(r, g, b, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 100.0, 0.0, 100.0);
}

/*
 * First recursive drawing function. Draws a branching tree.
 * Input: startpoint, branch length, angle (counter-clockwise from right)
 */
void drawPattern1(float x, float y, float length, float angle)
{
	if (length >= 1)
	{
		// calculate endpoint
		float x2 = x + ( length * cosD(angle) );
		float y2 = y + ( length * sinD(angle) );

		// draw line
		glColor3f(0.0, 0.5, 0.0);	// green
		glBegin(GL_LINES);
			glVertex2f(x, y);
			glVertex2f(x2, y2);
		glEnd();

		// recurse 2 times
		drawPattern1(x2, y2, length * 0.8, angle + 30);
		drawPattern1(x2, y2, length * 0.8, angle - 30);
	}
}

/*
 * Second recursive drawing function. Draws a Sierpinski triangle (using equilateral triangles).
 * Input: centre point, side length
 */
void drawPattern2(float x, float y, float length)
{
	if (length >= 1)
	{
		// calculate triangle height
		float height = sqrt( pow(length, 2) - pow(length / 2, 2) );

		// draw large triangle
		glColor3f(0.0, 0.0, 0.0);	// black
		glBegin(GL_TRIANGLES);
			glVertex2f( x - (length / 2), y - (height / 2) );	// bottom left
			glVertex2f( x + (length / 2), y - (height / 2) );	// bottom right
			glVertex2f( x, y + (height / 2) );					// top
		glEnd();

		// draw small triangle with gradient (white to purple)
		glBegin(GL_TRIANGLES);
			glColor3f(1.0, length / 100, 1.0);	// purple (as length decreases, saturation increases)
			glVertex2f( x, y - (height / 2) );	// bottom
			glColor3f(1.0, 1.0, 1.0);			// white
			glVertex2f( x - (length / 4), y );	// top left
			glVertex2f( x + (length / 4), y );	// top right
		glEnd();

		// recurse 3 times
		drawPattern2( x - (length / 4), y - (height / 4), length / 2 );	// bottom left
		drawPattern2( x + (length / 4), y - (height / 4), length / 2 );	// bottom right
		drawPattern2( x, y + (height / 4), length / 2 );				// top
	}
}

/*
 * Third recursive drawing function. Draws a Koch snowflake (using line segments).
 * Input: startpoint, endpoint, angle (counter-clockwise from right), if it is first function call
 */
void drawPattern3(float xStart, float yStart, float xEnd, float yEnd, float angle, bool isFirst)
{
	// calculate line length
	float length = sqrt( pow(xEnd - xStart, 2) + pow(yEnd - yStart, 2) );

	if (isFirst)
	{
		// draw line
		glColor3f(0.0, 0.0, 1.0);	// blue
		glBegin(GL_LINES);
			glVertex2f(xStart, yStart);
			glVertex2f(xEnd, yEnd);
		glEnd();

		// recurse 1 time
		drawPattern3(xStart, yStart, xEnd, yEnd, angle, false);
	}

	else if (length >= 4)
	{
		/* calculate 5 key points on line */

		// calculate points 1, 5 - endpoints
		float x1, y1;
		float x5, y5;

		if (xStart <= xEnd)
		{
			x1 = xStart;
			y1 = yStart;
			x5 = xEnd;
			y5 = yEnd;
		}

		else
		{
			x1 = xEnd;
			y1 = yEnd;
			x5 = xStart;
			y5 = yStart;
		}

		// calculate point 2 - closer to point 1
		float x2 = (2 * x1 + x5) / 3;
		float y2 = (2 * y1 + y5) / 3;

		// calculate point 4 - closer to point 5
		float x4 = (x1 + 2 * x5) / 3;
		float y4 = (y1 + 2 * y5) / 3;

		// calculate point 3 - top of triangle
		float height = sqrt( pow(length / 3, 2) - pow(length / 6, 2) );
		float x3 = ( (x2 + x4) / 2 ) + ( height * cosD(angle) );
		float y3 = ( (y2 + y4) / 2 ) + ( height * sinD(angle) );

		// draw line to erase triangle base
		glColor3f(1.0, 1.0, 1.0);	// white
		glBegin(GL_LINES);
			glVertex2f(x2, y2);
			glVertex2f(x4, y4);
		glEnd();

		// draw 2 lines (triangle sides)
		glColor3f(0.0, 0.0, 1.0);	// blue
		glLineWidth(2.0);			// double line thickness
		glBegin(GL_LINES);
			glVertex2f(x2, y2);
			glVertex2f(x3, y3);

			glVertex2f(x3, y3);
			glVertex2f(x4, y4);
		glEnd();

		// recurse 4 times
		if (0 <= angle and angle <= 180)
		{
			drawPattern3(x1, y1, x2, y2, angle, false);
			drawPattern3(x2, y2, x3, y3, angle + 60, false);
			drawPattern3(x3, y3, x4, y4, angle - 60, false);
			drawPattern3(x4, y4, x5, y5, angle, false);
		}

		else
		{
			drawPattern3(x1, y1, x2, y2, angle, false);
			drawPattern3(x2, y2, x3, y3, angle - 60, false);
			drawPattern3(x3, y3, x4, y4, angle + 60, false);
			drawPattern3(x4, y4, x5, y5, angle, false);
		}
	}
}

/*
 * Updates display.
 */
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);


	/* choose pattern 1, 2, or 3 */

	// drawPattern1(50.0, 15.0, 16.0, 90.0);

	// drawPattern2(50.0, 50.0, 80.0);

	// drawPattern3(20.0, 30.0, 80.0, 30.0, 270.0, true);	// bottom edge
	// drawPattern3(20.0, 30.0, 50.0, 82.0, 150.0, true);	// left edge
	// drawPattern3(50.0, 82.0, 80.0, 30.0, 30.0, true);	// right edge


	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Recursive Fractal Patterns!");
	init2D(1.0, 1.0, 1.0);	// white
	glutDisplayFunc(display);
	glutMainLoop();
}
