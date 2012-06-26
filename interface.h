#include <cstring>
#include <sstream>
//using namespace sf;

static sf::RenderWindow App(sf::VideoMode(563,600,32),"Solid Snake");

class Interface{
public:
	Game game;
	sf::Font font;
	bool gameStarted;

	Interface();
	void startGame();
	void loseGame();
	void nextLevel();
	void drawMenu();//sf::RenderWindow& App);
	void handleEvents(bool started);//sf::RenderWindow& App);

	void maine();//sf::RenderWindow& App);
	void drawHUD();//sf::RenderWindow& App);
	std::string toString(const int& value);
};