enum Cell{BONUS, BIGBONUS, EMPTY, WALL, SNAKE};

class Level{

public:
	int nbLv;
	int sizeLv;
	float timer;

	Level(int nbLevel);
	Level();
	Cell getCurrentCell(int x, int y);
	Cell getNextCell(int x, int y, Dir direction);
	//void loadLevel(int n);
	void loadWalls();
	void addBonus(Bonus b);
	void addBigBonus(BigBonus b);
	void eatBonus(Bonus b);
	void draw();
	void clearSnakeCells();
	void setCell(int x, int y, Cell type);

private:
	Cell cells[31][31];
};

const float timers[] = {0.3,0.15};

const int levelSize[] = {22,50};

const int levels[][900][2] = 
{
	{
		{10,10}, {10,11}, {10,12}, {10,13}, {10,14}, {10,15}, {10,16}, {10,17}, {10,18}, {10,19},
		{10,20}, {20,10}, {20,11}, {20,12}, {20,13}, {20,14}, {20,15}, {20,16}, {20,17}, {20,18},
		{20,19}, {20,20}
	},

	{
		{10,10}, {10,11}, {10,12}, {10,13}, {10,14}, {10,15}, {11,10}, {12,10}, {13,10}, {14,10},
		{15,10}, {16,10}, {17,10}, {18,10}, {19,10}, {20,10}, {20,11}, {20,12}, {20,13}, {20,14},
		{20,15}, {10,20}, {11,20}, {12,20}, {13,20}, {14,20}, {15,20}, {16,20}, {17,20}, {18,20},
		{19,20}, {20,20}, {15,21}, {15,22}, {15,23}, {15,24}, {15,25}, {15,26}, {15,27}, {15,28},
		{15,29}, {15,30}, {05,05}, {05,04}, {04,05}, {04,04}, {25,25}, {25,26}, {26,25}, {26,26}
	}
};

/*

{21,20}, {22,20}, {23,20}, {24,20}, {25,20}, {26,20}, {27,20}, {28,20},
		{29,20}, {30,20}

*/