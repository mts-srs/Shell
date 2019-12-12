#include "ProgramsState.h"

void ProgramsState::initBackground()
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

void ProgramsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/AppleGaramond.ttf"))
	{
		throw("ERROR:could not load font");
	}
}

void ProgramsState::initButtons()
{
	this->buttons["HELP"] = new Button(900, 750, 50, 50, &this->font, "Help", event);
	this->buttons["STEP"] = new Button(950, 750, 50, 50, &this->font, "Step", event);
	this->buttons["BACK"] = new Button(0, 750, 50, 50, &this->font, "Back", event);

	this->buttons["CREATE_PROCESS"] = new Button(350, 100, 300, 100, &this->font, "Create process", event);
	this->buttons["DELETE_PROCESS"] = new Button(350, 250, 300, 100, &this->font, "Delete process", event);
}

ProgramsState::ProgramsState(sf::RenderWindow *window, std::stack<State*> *states, sf::Event *event)
	:State(window, states, event)
{
	
	this->initFonts();
	this->initButtons();
	this->initBackground();
}

ProgramsState::~ProgramsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

void ProgramsState::endState()
{

}

void ProgramsState::updateKeybinds(const float& dt)
{
	this->checkForQuit();
}

void ProgramsState::update(const float& dt)
{
	if (event->type == sf::Event::MouseButtonReleased) {
		isMousePressed = false;
	}
	this->updateKeybinds(dt);
	this->updateMousePositions();
	this->updateTimebar();
	this->updateButtons();

}

void ProgramsState::updateButtons()
{
	//updating buttons and does all funcionality
	for (auto &it : this->buttons) {
		it.second->update(this->mousePosView);
	}

	if (this->buttons["CREATE_PROCESS"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->push(new CreateProcessInput(this->window, this->states, this->event));
	}

	if (this->buttons["DELETE_PROCESS"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->push(new DeleteProcessInput(this->window, this->states, this->event));
	}
		
	if (this->buttons["HELP"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->push(new HelpState(this->window, this->states, this->event));
	}

	//Quiting shell
	if (this->buttons["BACK"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->pop();
		system("cls");
	}

}

void ProgramsState::updateTimebar()
{
	this->timebar.getActualTime();
}

void ProgramsState::renderButtons(sf::RenderTarget * target)
{
	for (auto &it : this->buttons) {
		it.second->render(target);
	}
}

void ProgramsState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}

	target->draw(this->background);
	this->renderButtons(target);
	this->timebar.render(target);

/*//Only for tests, remove later
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(16);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());&

	target->draw(mouseText); */
}
