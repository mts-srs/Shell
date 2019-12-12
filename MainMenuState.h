#pragma once
#include "State.h"
#include "Button.h"
#include "Timebar.h"
#include "ProgramsState.h"
#include "FileManagerState.h"
#include "ControlPanelState.h"

extern bool isMousePressed;

class MainMenuState :
	public State
{
private:
	//variables
	TimeBar timebar = TimeBar(1000.f, 50.f, &font, "Main menu");
	sf::Texture texture;
	sf::Font font;
	sf::RectangleShape background;
	std::map<std::string, Button*> buttons;

	//Functions
	void initBackground();
	void initFonts();
	void initButtons();

public:
	MainMenuState(sf::RenderWindow *window, std::stack<State*> *states, sf::Event *event);
	virtual ~MainMenuState();

	//Functions
	void endState();
	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void updateButtons();
	void updateTimebar();
	void renderButtons(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr);
};

