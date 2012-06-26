class Bonus{

public:
	double x;
	double y;

	Bonus();
	Bonus(double xp, double yp);
	void draw();
};

class BigBonus: public Bonus{

public:
	int life;

	BigBonus();
	BigBonus(double xp, double yp);
	void draw();
};