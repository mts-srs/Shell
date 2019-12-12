#pragma once

#include<vector>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>
#include <map>

extern bool isMousePressed;

class State
{
	protected:
	std::stack<State*> *states; //To nie jest kopia states z shell tylko wskaznik na wlasnie tamtn stos zeby móc mieæ do nie go dostêp
	sf::RenderWindow *window;
	sf::Event *event;
	std::vector<sf::Texture> textures;
	bool quit;


	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

public:
	
	State(sf::RenderWindow *window, std::stack<State*> *states, sf::Event *event);
	virtual ~State();

	const bool& getQuit() const;

	virtual void checkForQuit();

	virtual void endState() = 0;
	virtual void updateMousePositions();
	virtual void updateKeybinds(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

