#include "ProcessSchedulingState.h"

void ProcessSchedulingState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	this->texture.loadFromFile("Resources/images/MMBackground.png");
	this->background.setTexture(&texture);
}

void ProcessSchedulingState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/AppleGaramond.ttf"))
	{
		throw("ERROR:MainMenuState could not load font");
	}
}

void ProcessSchedulingState::initButtons()
{
	this->buttons["HELP"] = new Button(900, 750, 50, 50, &this->font, "Help", event);
	this->buttons["STEP"] = new Button(950, 750, 50, 50, &this->font, "Step", event);
	this->buttons["BACK"] = new Button(0, 750, 50, 50, &this->font, "Back", event);

	this->buttons["PCBQUEUE"] = new Button(350, 100, 300, 100, &this->font, "PCB queue", event);
	this->buttons["RUNNING"] = new Button(350, 250, 300, 100, &this->font, "Running", event);
}

ProcessSchedulingState::ProcessSchedulingState(sf::RenderWindow *window, std::stack<State*> *states, sf::Event *event)
	:State(window, states, event)
{

	this->initFonts();
	this->initButtons();
	this->initBackground();
}

ProcessSchedulingState::~ProcessSchedulingState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

void ProcessSchedulingState::endState()
{

}

void ProcessSchedulingState::updateKeybinds(const float& dt)
{
	this->checkForQuit();
}

void ProcessSchedulingState::update(const float& dt)
{
	if (event->type == sf::Event::MouseButtonReleased) {
		isMousePressed = false;
	}
	this->updateKeybinds(dt);
	this->updateMousePositions();
	this->updateTimebar();
	this->updateButtons();

}

void ProcessSchedulingState::updateButtons()
{
	if (this->buttons["HELP"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->push(new HelpState(this->window, this->states, this->event));
	}

	//updating buttons and does all funcionality
	for (auto &it : this->buttons) {
		it.second->update(this->mousePosView);
	}

	//Quiting shell
	if (this->buttons["BACK"]->isPressed() && isMousePressed == false) {
		isMousePressed = true;
		this->states->pop();
		system("cls");
	}

}

void ProcessSchedulingState::updateTimebar()
{
	this->timebar.getActualTime();
}

void ProcessSchedulingState::renderButtons(sf::RenderTarget * target)
{
	for (auto &it : this->buttons) {
		it.second->render(target);
	}
}

void ProcessSchedulingState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}

	target->draw(this->background);
	this->renderButtons(target);
	this->timebar.render(target);

	//Only for tests, remove later
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(16);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);*/
}
