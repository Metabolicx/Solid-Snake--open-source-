class Game{

public:
	int score;
	int nbEatenBonus;
	bool pause;
	float timer;
	int moves;
	int totalMoves;
	bool loose;
	int levelNb;

	Game();
	void handleEvents(const sf::Input& Input, bool started);
	void moveSnake();
	void draw();
	void youLose();
	void newGame();
	void handleBonus();
	void maine(sf::Window& App);
	void nextLevel();

private:
	BigBonus bigBonus;
	Bonus bonus;
	Snake snake;
	Level level;
	bool ifBigBonus;
	bool ifBonus;
	sf::Clock Clock;

	void updateSnakeCells();
	Cell getCurrentCell();
	Cell getNextCell();
	void addBonus();
	void eatBonus();
	void eatBigBonus();
	void addBigBonus();
	void delBigBonus();
};

