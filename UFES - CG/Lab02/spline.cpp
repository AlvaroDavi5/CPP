#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <GL/glut.h>

#define WINDOW_SIZE 500
#define PIXEL_POSITION_COMPENSATION 100
float size = 1.0;

// spline control points
GLfloat ctrlpoints[4][3] = {
		{0.1, 0.2, 0.0}, {0.3, 0.8, 0.0}, {0.6, 0.2, 0.0}, {0.8, 0.8, 0.0}};

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_MAP1_VERTEX_3);

	// polynomial definition with control points
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);

	// change to projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0 * -size, size, 0.0 * -size, size, -size, size);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// drawn control points
	glPointSize(5.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 4; i++)
		glVertex3fv(&ctrlpoints[i][0]);
	glEnd();

	// drawn the curve for n+1 points
	const int n = 30;
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= n; i++)
	{
		// polynomial avaliation, returns a vertice (likes glVertex3fv)
		const float rt = (GLfloat)i / (GLfloat)n;
		float coordX = ctrlpoints[0][0] * ctrlpoints[1][0] * ctrlpoints[2][0] * ctrlpoints[3][0];
		float coordY = ctrlpoints[0][1] * ctrlpoints[1][1] * ctrlpoints[2][1] * ctrlpoints[3][1];
		glEvalCoord1f(rt * (coordX + coordY));
	}
	glEnd();

	glutSwapBuffers();
}

bool isAround(float v1, float v2)
{
	const float limitValue = 0.030;

	if (v1 >= (v2 - limitValue) && v1 <= (v2 + limitValue))
		return true;
	else
		return false;
}

void mouseControl(int x, int y)
{
	float posX = 0.0, posY = 0.0;

	y = WINDOW_SIZE - y;
	posX = float(x) / float(WINDOW_SIZE);
	posY = float(y) / float(WINDOW_SIZE);

	if (isAround(posX, ctrlpoints[0][0]) && isAround(posY, ctrlpoints[0][1]))
	{
		ctrlpoints[0][0] = posX;
		ctrlpoints[0][1] = posY;
	}
	else if (isAround(posX, ctrlpoints[1][0]) && isAround(posY, ctrlpoints[1][1]))
	{
		ctrlpoints[1][0] = posX;
		ctrlpoints[1][1] = posY;
	}
	else if (isAround(posX, ctrlpoints[2][0]) && isAround(posY, ctrlpoints[2][1]))
	{
		ctrlpoints[2][0] = posX;
		ctrlpoints[2][1] = posY;
	}
	else if (isAround(posX, ctrlpoints[3][0]) && isAround(posY, ctrlpoints[3][1]))
	{
		ctrlpoints[3][0] = posX;
		ctrlpoints[3][1] = posY;
	}

	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutMotionFunc(mouseControl);
	glutMainLoop();
	return 0;
}
