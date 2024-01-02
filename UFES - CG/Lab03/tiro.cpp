#include "tiro.h"
#include <math.h>
#define DISTANCIA_MAX 500

void Tiro::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
	const int lineAmount = 18; // 360/20=18
	const GLfloat twicePi = 2.0f * M_PI;

	glColor3f(R, G, B);

	glBegin(GL_POLYGON);
	for (int i = 1; i <= lineAmount; i++)
	{
		glVertex3f(
				(radius * cos(i * twicePi / lineAmount)),
				(radius * sin(i * twicePi / lineAmount)),
				0.0);
	}
	glEnd();
}

void Tiro::DesenhaTiro(GLfloat x, GLfloat y)
{
	glPushMatrix();
	glTranslatef(x, y, 0.0);
	DesenhaCirc(radiusTiro, 0.5, 0.0, 0.5);
	glPopMatrix();
}

void Tiro::Move()
{
	this->gX += this->gVel * cos(this->gDirectionAng);
	this->gY += this->gVel * sin(this->gDirectionAng);
}

bool Tiro::Valido()
{
	if (this->gX < -DISTANCIA_MAX || this->gX > DISTANCIA_MAX ||
			this->gY < -DISTANCIA_MAX || this->gY > DISTANCIA_MAX)
		return false;
	else
		return true;
}
