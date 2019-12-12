#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include <iostream>
#include <string>

extern bool isMousePressed;

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

class Button
{
private:
	short unsigned buttonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;
	sf::Event *event;

	sf::Texture idleTexture;
	sf::Texture hoverTexture;
	sf::Texture activeTexture;

public:
	Button(float x, float y, float width, float height, sf::Font* font,
		std::string text, sf::Event *event);
	virtual ~Button();

	//Accessors
	const bool isPressed() const;

	//functions
	void update(sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};

