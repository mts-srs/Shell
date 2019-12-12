#include "MainMenuState.h"

void MainMenuState::initBackground()
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

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/AppleGaramond.ttf")) 
	{
		throw("ERROR:could not load font");
	}
}

void MainMenuState::initButtons()
{
	this->buttons["HELP"] = new Button(900, 750, 50, 50, &this->font, "Help", event);
	this->buttons["STEP"] = new Button(950, 750, 50, 50, &this->font, "Step", event);

	this->buttons["PROGRAMS"] = new Button(350, 100, 300, 100, &this->font, "Programs", event);
	this->buttons["FILE_MANAGER"] = new Button(350, 250, 300, 100, &this->font, "File manager", event);
	this->buttons["CONTROL_PANEL"] = new Button(350, 400, 300, 100, &this->font, "Control panel", event);
	this->buttons["EXIT"] = new Button(350, 550, 300, 100, &this->font, "Quit", event);
}

MainMenuState::MainMenuState(sf::RenderWindow *window, std::stack<State*> *states, sf::Event *event)
	:State(window, states, event)
{
	this->initFonts();
	this->initButtons();
	this->initBackground();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

void MainMenuState::endState()
{

}

void MainMenuState::updateKeybinds(const float& dt)
{
	this->checkForQuit();
}

void MainMenuState::update(const float& dt)
{
	if (event->type == sf::Event::MouseButtonReleased) {
		isMousePressed = false;
	}
	this->updateKeybinds(dt);
	this->updateMousePositions();
	this->updateTimebar();
	this->updateButtons();

}

void MainMenuState::updateButtons()
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

	if (this->buttons["PROGRAMS"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		// && event->type == sf::Event::MouseButtonReleased
		std::cout << "PROBA RAZ DWA CZY";
		this->states->push(new ProgramsState(this->window, this->states, this->event));
	}

	if (this->buttons["FILE_MANAGER"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->push(new FileManagerState(this->window, this->states, this->event));
	}

	if (this->buttons["CONTROL_PANEL"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->push(new ControlPanelState(this->window, this->states, this->event));
	}

	//Quiting shell
	if (this->buttons["EXIT"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->quit = true;	
	}

}

void MainMenuState::updateTimebar()
{
	this->timebar.getActualTime();
}

void MainMenuState::renderButtons(sf::RenderTarget * target)
{
	for (auto &it : this->buttons) {
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}

	target->draw(this->background);
	this->renderButtons(target);
	this->timebar.render(target);

	//Only for tests, remove later
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
