#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font * font, std::string text, sf::Event *event)
{
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->event = event;
	this->buttonState = BTN_IDLE;
	
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(20);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

	this->idleTexture.loadFromFile("Resources/Images/ButtonNormal.png");
	this->hoverTexture.loadFromFile("Resources/Images/ButtonHover.png");
	this->activeTexture.loadFromFile("Resources/Images/ButtonClicked.png");
}

Button::~Button()
{

}

//Accesors

const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;

	return false;
}


//Functions

void Button::update(const sf::Vector2f mousePos)
{
	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos)) 
	{
		this->buttonState = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setTexture(&this->idleTexture);
		break;

	case BTN_HOVER:
		this->shape.setTexture(&this->hoverTexture);	
		break;

	case BTN_ACTIVE:
		this->shape.setTexture(&this->activeTexture);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
	target->draw(this->text);
}
