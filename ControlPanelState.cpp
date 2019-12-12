#include "ControlPanelState.h"

void ControlPanelState::initBackground()
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

void ControlPanelState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/AppleGaramond.ttf"))
	{
		throw("ERROR:could not load font");
	}
}

void ControlPanelState::initButtons()
{
	this->buttons["HELP"] = new Button(900, 750, 50, 50, &this->font, "Help", event);
	this->buttons["STEP"] = new Button(950, 750, 50, 50, &this->font, "Step", event);
	this->buttons["BACK"] = new Button(0, 750, 50, 50, &this->font, "Back", event);

	this->buttons["VM"] = new Button(100, 100, 200, 100, &this->font, "VM", event);
	this->buttons["RAM"] = new Button(600, 100, 200, 100, &this->font, "RAM", event);

	this->buttons["DISC"] = new Button(100, 250, 200, 100, &this->font, "Disc", event);
	this->buttons["PROCSCHE"] = new Button(600, 250, 200, 100, &this->font, "Process scheduling", event); //pjoter

	this->buttons["COMMUNICATION"] = new Button(100, 400, 200, 100, &this->font, "Communication", event);
	this->buttons["PROCMANA"] = new Button(600, 400, 200, 100, &this->font, "Processes management", event); //eryk
}

ControlPanelState::ControlPanelState(sf::RenderWindow *window, std::stack<State*> *states, sf::Event *event)
	:State(window, states, event)
{
	this->initFonts();
	this->initButtons();
	this->initBackground();
}

ControlPanelState::~ControlPanelState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

void ControlPanelState::endState()
{

}

void ControlPanelState::updateKeybinds(const float& dt)
{
	this->checkForQuit();
}

void ControlPanelState::update(const float& dt)
{
	if (event->type == sf::Event::MouseButtonReleased) {
		isMousePressed = false;
	}
	this->updateKeybinds(dt);
	this->updateMousePositions();
	this->updateTimebar();
	this->updateButtons();

}

void ControlPanelState::updateButtons()
{
	//updating buttons and does all funcionality
	for (auto &it : this->buttons) {
		it.second->update(this->mousePosView);
	}

	if (this->buttons["HELP"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->push(new HelpState(this->window, this->states, this->event));
	}

	if (this->buttons["VM"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->push(new VMState(this->window, this->states, this->event));
	}

	if (this->buttons["RAM"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->push(new RAMState(this->window, this->states, this->event));
	}

	if (this->buttons["DISC"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->push(new DiscState(this->window, this->states, this->event));
	}

	if (this->buttons["COMMUNICATION"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->push(new CommunicationState(this->window, this->states, this->event));
	}

	if (this->buttons["PROCMANA"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->push(new ProcessesManagementState(this->window, this->states, this->event));
	}

	if (this->buttons["PROCSCHE"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->push(new ProcessSchedulingState(this->window, this->states, this->event));
	}

	//Quiting shell
	if (this->buttons["BACK"]->isPressed() && isMousePressed == false) {
		isMousePressed = true;
		this->states->pop();
		system("cls");
	}

}

void ControlPanelState::updateTimebar()
{
	this->timebar.getActualTime();
}

void ControlPanelState::renderButtons(sf::RenderTarget * target)
{
	for (auto &it : this->buttons) {
		it.second->render(target);
	}
}

void ControlPanelState::render(sf::RenderTarget* target)
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
