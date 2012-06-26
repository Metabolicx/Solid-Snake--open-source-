#include "bonus.h"

Bonus::Bonus(double xp, double yp)
{
	x = xp;
	y = yp;
}

Bonus::Bonus()
{

}

void Bonus::draw()
{
	double circlex;
	double circley;
	glColor3ub(255,0,0);
	glBegin(GL_LINES);
	for(int i=0;i<180;i++){
		circlex = cos(i)/2 + x;
		circley = sin(i)/2 + y;
		glVertex3f(circlex, circley, 0);
	}
	glEnd();
}

BigBonus::BigBonus(double xp, double yp)
{
	x = xp;
	y = yp;
	life = 0;
}

BigBonus::BigBonus()
{

}

void BigBonus::draw()
{
	double circlex;
	double circley;
	glColor3ub(255,0,0);
	glBegin(GL_LINES);
	for(int i=0;i<180;i++){
		circlex = cos(i)/2 + x;
		circley = sin(i)/2 + y;
		glVertex3f(circlex, circley, 0);
		glVertex3f(x, y, 0);
	}
	glEnd();
}