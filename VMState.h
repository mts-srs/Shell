#pragma once
#include "State.h"
#include "Button.h"
#include "Timebar.h"
#include "HelpState.h"

extern bool isMousePressed;


class VMState :
	public State
{
private:
	//variables
	TimeBar timebar = TimeBar(1000.f, 50.f, &font, "Virtual Memory");
	sf::Texture texture;
	sf::Font font;
	sf::RectangleShape background;
	std::map<std::string, Button*> buttons;

	//Functions
	void initBackground();
	void initFonts();
	void initButtons();

public:
	VMState(sf::RenderWindow *window, std::stack<State*> *states, sf::Event *event);
	virtual ~VMState();

	//Functions
	void endState();
	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void updateButtons();
	void updateTimebar();
	void renderButtons(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr);
};