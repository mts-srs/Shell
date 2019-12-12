#pragma once
#include "State.h"
#include "Button.h"
#include "Timebar.h"
#include "InputField.h"

extern bool isMousePressed;

class CreateProcessInput :
	public State
{
private:
	//variables
	TimeBar timebar = TimeBar(1000.f, 50.f, &font, "Type name, file, priority");
	sf::Texture texture;
	sf::Font font;
	sf::RectangleShape background;
	std::map<std::string, Button*> buttons;
	InputField input = InputField(&font, event);


	//Functions
	void initBackground();
	void initFonts();
	void initButtons();

public:
	CreateProcessInput(sf::RenderWindow *window, std::stack<State*> *states, sf::Event *event);
	virtual ~CreateProcessInput();

	//Functions
	void endState();
	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void updateButtons();
	void updateTimebar();
	void updateInput();
	void renderButtons(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr);
};