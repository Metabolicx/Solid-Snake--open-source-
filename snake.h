struct Part{
	double x;
	double y;
	bool orient;
};

enum Dir{UP, RIGHT, LEFT, DOWN, STILL};

class Snake{

public:
	Dir direction;
	bool bonusEaten;

	Snake();
	void addPart(double x, double y);
	void draw();
	void moveSnake();
	Part getHeadPosition();
	Part getPartPosition(int i);
	void eatBonus();
	void nextLevel();
	//void reset();
	int getLength();

private:
	std::vector<Part> parts;
	void nextState();
};
