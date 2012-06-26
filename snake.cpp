#include "snake.h"


Snake::Snake()
{
	direction = STILL;
	bonusEaten = false;
	addPart(0,0);
	addPart(0,1);
	addPart(0,2);
}

void Snake::addPart(double x, double y)
{
	Part niou;
	niou.x = x;
	niou.y = y;
	niou.orient = 0;
	parts.push_back(niou);
}

/*
void Snake::reset()
{
	parts.clear();
	direction = STILL;
	bonusEaten = false;
	addPart(0,0);
	addPart(0,1);
	addPart(0,2);
}
*/

void Snake::eatBonus()
{
	bonusEaten = true;
}

void Snake::draw()
{
	double circlex;
	double circley;
	int c = 0;
	double x,y;


	glColor3ub(0,100,190);

	int size = parts.size();

	for(int j=0; j<size; j++)
	{
		x = parts[j].x;
		y = parts[j].y;

		glBegin(GL_LINES);
		for(int i=0;i<180;i++){
			circlex = cos(i)/2 + x;
			circley = sin(i)/2 + y;
			glVertex3f(circlex, circley, 0);
			glVertex3f(x, y, 0);
		}
		glEnd();
		glColor3ub(0,0,0);
		glBegin(GL_QUADS);

		if(parts[j-1].orient != parts[j].orient){}

		else if(parts[j].orient){
			glVertex3f(x-0.5,y+0.6,0);
			glVertex3f(x+0.5,y+0.6,0);
			glVertex3f(x+0.5,y+0.4,0);
			glVertex3f(x-0.5,y+0.4,0);
		
			glVertex3f(x-0.5,y-0.6,0);
			glVertex3f(x-0.5,y-0.4,0);
			glVertex3f(x+0.5,y-0.4,0);
			glVertex3f(x+0.5,y-0.6,0);
		}
		else{
			glVertex3f(x-0.6,y+0.5,0);
			glVertex3f(x-0.4,y+0.5,0);
			glVertex3f(x-0.4,y-0.5,0);
			glVertex3f(x-0.6,y-0.5,0);
		
			glVertex3f(x+0.4,y+0.5,0);
			glVertex3f(x+0.6,y+0.5,0);
			glVertex3f(x+0.6,y-0.5,0);
			glVertex3f(x+0.4,y-0.5,0);
		}
		glEnd();

		c += 5;
		glColor3ub(c,255,c);
	}
	glFlush();
}

Part Snake::getHeadPosition()
{
	return parts.front();
}

Part Snake::getPartPosition(int i)
{
	if(i < parts.size())
		return parts[i];
	else
		std::cout << "SegFault getPosition" << i << std::endl;
}

int Snake::getLength()
{
	return parts.size();
}

void debug(Part p)
{
	std::cout << "(" << p.x << "," << p.y << ") : " << p.orient << "/ ";
}

void Snake::nextState()
{
	std::cout << "nextstate" << std::endl;
	debug(parts.front());
	Part niou;
	if(bonusEaten)
		niou = parts.back();
	int size = parts.size();
	for(int i=size-1; i>0; i--)
	{
		std::cout << i << ":";
		debug(parts[i]);
		parts[i].x = parts[i-1].x;
		parts[i].y = parts[i-1].y;
		parts[i].orient = parts[i-1].orient;
	}
	std::cout << std::endl;
	if(bonusEaten){
		std::cout << "## APPEND ##";
		debug(niou);
		parts.push_back(niou);
		bonusEaten = false;
	}
}

void Snake::moveSnake()
{
	if(direction != STILL)
		nextState();

	switch(direction){
		case LEFT:
			if(parts.front().x <= -15)
				parts.front().x = 15;
			else
				parts.front().x -= 1;
			parts.front().orient = 1;
			break;
		case RIGHT:
			if(parts.front().x >= 15)
				parts.front().x = -15;
			else
				parts.front().x += 1;
			parts.front().orient = 1;
			break;
		case UP:
			if(parts.front().y >= 15)
				parts.front().y = -15;
			else
				parts.front().y += 1;
			parts.front().orient = 0;
			break;
		case DOWN:
			if(parts.front().y <= -15)
				parts.front().y = 15;
			else
				parts.front().y -= 1;
			parts.front().orient = 0;
			break;
		default:
			break;
	}
}
