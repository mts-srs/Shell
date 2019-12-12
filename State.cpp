#include "State.h"

State::State(sf::RenderWindow *window, std::stack<State*> *states, sf::Event *event)
{
	this->window = window;
	this->window->setKeyRepeatEnabled(false);
	this->states = states;
	this->event = event;
	this->quit = false;
}


State::~State()
{
}

const bool & State::getQuit() const
{
	return this->quit;
}

void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->quit = true;
	}
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

}
