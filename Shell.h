#pragma once
#include"MainMenuState.h"

extern bool isMousePressed;

class Shell
{
private:
	//Variables
	sf::RenderWindow *window;
	sf::Event sfevent;
	std::vector<sf::VideoMode> videoModes;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	//Initialization
	void initWindow();
	void initStates();

public:
	Shell();
	virtual ~Shell();

	void endApplication();

	//Functions
	void updateDt();
	void updateSFMLEvents();
	void update();

	//render
	void render();

	//core
	void run();	
};

