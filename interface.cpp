#include "interface.h"

Interface::Interface()
{
	App.SetFramerateLimit(60);
    App.PreserveOpenGLStates(true);

    game = Game();
	gameStarted = false;
	if(!font.LoadFromFile("GenBasR.ttf"))
		std::cout << "Erreur lors du chargement de la police." << std::endl;
}

void Interface::maine()//sf::RenderWindow& App)
{
	while (App.IsOpened())
	{
		sf::Event Event;
		while (App.GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
                App.Close();

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
                App.Close();

            if (Event.Type == sf::Event::Resized)
                glViewport(0, 0, Event.Size.Width, Event.Size.Height);
        }

        handleEvents(gameStarted);

		if(game.loose)
			gameStarted = false;

		if(gameStarted){
			if(game.nbEatenBonus == 20)
				game.nextLevel();
			game.maine(App);
			drawHUD();//App);
		}
		else{
			drawMenu();//App);
		}

		App.Display();
	}
}

void Interface::drawMenu()//sf::RenderWindow& App)
{
	std::string line = "Press Enter to Start\nQ: Quit\nR: Restart\nSpace: Pause";
	sf::String text(line, font, 30);
	text.SetColor(sf::Color(200,120,20));
	text.SetPosition(50,50);
	App.Draw(text);
}

void Interface::handleEvents(bool started)//sf::RenderWindow& App)
{
	const sf::Input& Input = App.GetInput();
	bool QKey = Input.IsKeyDown(sf::Key::Q);
	bool EnterKey = Input.IsKeyDown(sf::Key::Return);
	bool RKey = Input.IsKeyDown(sf::Key::R);

	game.handleEvents(Input,started);

	if(EnterKey){
		gameStarted = true;
		if(game.loose){
			game.loose = false;
			game = Game();
		}
	}

	if(QKey)
		App.Close();

	if(RKey){
		game = Game();
		gameStarted = false;
	}

}

std::string Interface::toString(const int& value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

void Interface::drawHUD()//sf::RenderWindow& App)
{
	std::string line = "Lv" + toString(game.levelNb + 1) + "     Score : " + toString(game.score);
	if(game.pause)
		line = line + "        PAUSED !";

	sf::String text(line, font, 30);
	//text.SetStyle(sf::String::Bold);
	text.SetColor(sf::Color(255,255,255));
	text.SetPosition(0,0);
	App.Draw(text);
}