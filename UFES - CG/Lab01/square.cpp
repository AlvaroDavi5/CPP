// lib headers
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>

// macros
#define WINDOW_SIZE 500
#define POSITION_ADJUST 0.50

// global variables
float gX = 0.0, gY = 0.0, s = 1.0;

void display(void)
{
	// clear display buffer for all pixels
	glClear(GL_COLOR_BUFFER_BIT);

	// set vertex colors using RGB scale ranging between 0.0 and 1.0
	glColor3f(0.5, 1.0, 0.7);

	// drawn a green polygon (square)
	glBegin(GL_POLYGON);
	glVertex3f(0.25 + gX, 0.25 + gY, 0.0);
	glVertex3f(0.75 + gX, 0.25 + gY, 0.0);
	glVertex3f(0.75 + gX, 0.75 + gY, 0.0);
	glVertex3f(0.25 + gX, 0.75 + gY, 0.0);
	glEnd();

	// drwan on frame buffer
	glutSwapBuffers();
}

void keyPress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		gY += (0.01);
		break;
	case 's':
		gY -= (0.01);
		break;
	case 'a':
		gX -= (0.01);
		break;
	case 'd':
		gX += (0.01);
		break;
	default:
		break;
	}

	// reload display
	glutPostRedisplay();
}

void mouseControl(int button, int state, int x, int y)
{
	float posX = 0.0, posY = 0.0;
	char buttonName[8] = "";

	y = WINDOW_SIZE - y; // invert Y aexis
	posX = float(x) / float(WINDOW_SIZE);
	posY = float(y) / float(WINDOW_SIZE);

	gX = (s * posX) + s * (-POSITION_ADJUST);
	gY = (s * posY) + s * (-POSITION_ADJUST);

	switch (button)
	{
	case 0:
		strcpy(buttonName, "left   ");
		s = +1.0;
		break;
	case 1:
		strcpy(buttonName, "middle ");
		gX = 0.0;
		gY = 0.0;
		s = 0.0;
		break;
	case 2:
		strcpy(buttonName, "right  ");
		s = -1.0;
		break;
	case 3:
		strcpy(buttonName, "scroll+");
		s = 0.0;
		break;
	case 4:
		strcpy(buttonName, "scroll-");
		s = 0.0;
		break;
	default:
		printf("%d\n", button);
		break;
	}

	printf("Mouse Button: (%d) %s   ", state, buttonName);
	printf("Mouse Position: X=%d, Y=%d\n", x, y);

	glutPostRedisplay();
}

void mouseUpdate(int x, int y)
{
	float posX = 0.0, posY = 0.0;

	y = WINDOW_SIZE - y;
	posX = float(x) / float(WINDOW_SIZE);
	posY = float(y) / float(WINDOW_SIZE);

	gX = (s * posX) + s * (-POSITION_ADJUST);
	gY = (s * posY) + s * (-POSITION_ADJUST);

	glutPostRedisplay();
}

void initView(void)
{
	// set background color
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// init view system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char **argv)
{
	// GLUT initialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// view window initialization
	glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Square");
	initView();

	// callbacks register
	glutDisplayFunc(display);
	// glutReshapeFunc(NULL);
	glutKeyboardFunc(keyPress);
	glutMouseFunc(mouseControl);
	glutMotionFunc(mouseUpdate); // glutPassiveMotionFunc

	// render loop
	glutMainLoop();

	return 0;
}
