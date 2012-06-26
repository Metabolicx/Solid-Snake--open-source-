#include "game.h"
#include <ctime>
#include <cstdlib>

Game::Game()
{
	snake = Snake();
	score = 0;
	level = Level();
	levelNb = 0;
	nbEatenBonus = 0;
	pause = false;
	timer = level.timer;
	moves = 0;
	totalMoves = 0;
	loose = false;
	ifBigBonus = false;
	ifBonus = false;
	updateSnakeCells();
}

void Game::handleEvents(const sf::Input& Input, bool started)
{
	Dir currDir = snake.direction;
	Dir nextDir = currDir;

	//const sf::Input& Input = App.GetInput();
	do{
		bool LeftKey = Input.IsKeyDown(sf::Key::Left);
		bool RightKey = Input.IsKeyDown(sf::Key::Right);
		bool UpKey = Input.IsKeyDown(sf::Key::Up);
		bool DownKey = Input.IsKeyDown(sf::Key::Down);
		bool SpaceKey = Input.IsKeyDown(sf::Key::Space);

		bool _SpaceKey = true;
		bool left, right, up, down;

		if(SpaceKey && _SpaceKey){
			pause = !pause;
			_SpaceKey = false;
		}
		if(LeftKey && currDir != RIGHT && !pause)
			nextDir = LEFT;
		if(RightKey && currDir != LEFT && !pause)
			nextDir = RIGHT;
		if(UpKey && currDir != DOWN && !pause)
			nextDir = UP;
		if(DownKey && currDir != UP && !pause)
			nextDir = DOWN;
	}while(started && Clock.GetElapsedTime() < timer);
	snake.direction = nextDir;
	Clock.Reset();
}

void Game::draw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	snake.draw();
	level.draw();
	if(ifBonus)
		bonus.draw();
	if(ifBigBonus)
		bigBonus.draw();

	glColor3ub(255,255,255);
	glBegin(GL_LINE);
	glVertex3f(-15.5,15.5,0);
	glVertex3f(15.5,15.5,0);
	glEnd();

	glFlush();
}

void Game::moveSnake()
{
	if(snake.direction == STILL || (getNextCell() != WALL && getNextCell() != SNAKE))
		snake.moveSnake();
	else if(snake.direction != STILL)
		youLose();

	if(getCurrentCell() == BONUS)
		eatBonus();

	if(getCurrentCell() == BIGBONUS)
		eatBigBonus();

	if(!ifBonus)
		addBonus();

	updateSnakeCells();

	if(snake.direction != STILL)
		moves++;
}

void Game::maine(sf::Window& App)
{
	if(!pause){
		std::cout << "Entrée boucle principale" << std::endl;
		std::cout << "Bonus : (" << bonus.x << "," << bonus.y << ")" <<std::endl;
		if(ifBigBonus)
			std::cout << "BigBonus : (" << bigBonus.x << "," << bigBonus.y << ") : " << bigBonus.life << std::endl;
		std::cout << "Moves : " << moves << std::endl;
		std::cout << "nbEatenBonus : " << nbEatenBonus << std::endl;
		std::cout << "Score : " << score << std::endl;

		//handleEvents(App);

		std::cout << "Evenements ok, prochaine cellule : " << getNextCell() << std::endl;
		
		moveSnake();

		std::cout << "Snake bougé : Position : (" << snake.getHeadPosition().x << "," << snake.getHeadPosition().y << ") " << snake.direction << std::endl;

		handleBonus();

		std::cout << "Bonus gérés" << std::endl;

		draw();
		std::cout << "Dessin ok, sortie de boucle principale" << std::endl;

		//sf::Sleep(timer);
	}
}

void Game::updateSnakeCells()
{
	level.clearSnakeCells();
	for(int i=0; i<snake.getLength(); i++)
	{
		Part curr = snake.getPartPosition(i);
		level.setCell(curr.x, curr.y, SNAKE);
	}
}

void Game::nextLevel()
{
	totalMoves += moves;
	nbEatenBonus = 0;
	moves = 0;
	levelNb++;
	level = Level(levelNb);
	timer = level.timer;
	snake = Snake();
	updateSnakeCells();
	ifBonus = false;
	ifBigBonus = false;
	Clock.Reset();
}

Cell Game::getNextCell()
{
	Part position = snake.getHeadPosition();
	return level.getNextCell((int)(position.x), (int)(position.y), snake.direction);
}

void Game::youLose()
{
	loose = true;
}

Cell Game::getCurrentCell()
{
	Part position = snake.getHeadPosition();
	return level.getCurrentCell((int)(position.x), (int)(position.y));
}

void Game::eatBonus()
{
	level.eatBonus(bonus);
	snake.eatBonus();
	score = score + 1+level.nbLv;
	ifBonus = false;
	nbEatenBonus++;
}

void Game::eatBigBonus()
{
	level.eatBonus(bigBonus);
	snake.eatBonus();
	score = score + 3 * (1+level.nbLv);
	ifBigBonus = false;
	nbEatenBonus++;
}

void Game::addBonus()
{
	double x,y;
	do{
		x = randomNb(-15,15);
		y = randomNb(-15,15);
	}while(level.getCurrentCell(x,y) != EMPTY);

	bonus = Bonus(x,y);
	level.addBonus(bonus);
	ifBonus = true;
}

void Game::addBigBonus()
{
	double x,y;
	do{
		x = randomNb(-15,15);
		y = randomNb(-15,15);
	}while(level.getCurrentCell(x,y) != EMPTY);

	bigBonus = BigBonus(x,y);
	level.addBigBonus(bigBonus);
	ifBigBonus = true;
}


void Game::handleBonus()
{
	if(moves % 50 == 0 && moves != 0)
		addBigBonus();
	if(ifBigBonus){
		if(!pause)
			bigBonus.life++;
		if(bigBonus.life >= 20)
			delBigBonus();
	}
}

void Game::delBigBonus()
{
	level.eatBonus(bigBonus);
	ifBigBonus = false;
}
