#include "level.h"


Level::Level(int nbLevel)
{
	nbLv = nbLevel;
	timer = timers[nbLevel];
	sizeLv = levelSize[nbLevel];
	loadWalls();
}

Level::Level()
{
	nbLv = 0;
	timer = timers[0];
	sizeLv = levelSize[0];
	loadWalls();
}


Cell Level::getCurrentCell(int x, int y)
{
	return cells[x+15][y+15];
}

Cell Level::getNextCell(int x, int y, Dir direction)
{
	switch(direction){
		case LEFT:
			if(x <= -15)
				return cells[30][y+15];
			else
				return cells[x+14][y+15];
			break;
		case DOWN:
			if(y <= -15)
				return cells[x+15][30];
			else
				return cells[x+15][y+14];
			break;
		case UP:
			if(y >= 15)
				return cells[x+15][0];
			else
				return cells[x+15][y+16];
			break;
		case RIGHT:
			if(x >= 15)
				return cells[0][y+15];
			else
				return cells[x+16][y+15];
			break;
		case STILL:
			return getCurrentCell(x,y);
	}
}

/*
void Level::loadLevel(int n)
{
	nbLv = n;
	timer = timers[nbLv];
	sizeLv = levelSize[nbLv];
	loadWalls();
}
*/

void Level::loadWalls()
{
	for(int i=0; i<=30; i++){
		for(int j=0; j<=30; j++){
			cells[i][j] = EMPTY;
		}
	}
	for(int i=0; i<sizeLv; i++)
	{
		cells[ levels[nbLv][i][0] ][ levels[nbLv][i][1] ] = WALL;
	}
}

void Level::addBonus(Bonus b)
{
	cells[(int)(b.x+15)][(int)(b.y+15)] = BONUS;
}

void Level::addBigBonus(BigBonus b)
{
	cells[(int)(b.x+15)][(int)(b.y+15)] = BIGBONUS;
}

void Level::eatBonus(Bonus b)
{
	cells[(int)(b.x+15)][(int)(b.y+15)] = EMPTY;
}

void Level::clearSnakeCells()
{
	for(int i=0; i<=30; i++){
		for(int j=0; j<=30; j++){
			if(cells[i][j] == SNAKE)
				cells[i][j] = EMPTY;
		}
	}
}

void Level::setCell(int x, int y, Cell type)
{
	cells[x+15][y+15] = type;
}

void Level::draw()
{
	glColor3ub(255,255,180);
	for(int y=0; y<=30; y++){
		for(int x=0; x<=30; x++){
			if(cells[x][y] == WALL)
				glBegin(GL_QUADS);
				glVertex3f(x-15.5, y-14.5, 0);
				glVertex3f(x-14.5, y-14.5, 0);
				glVertex3f(x-14.5, y-15.5, 0);
				glVertex3f(x-15.5, y-15.5, 0);
				glEnd();

		}
	}
}