#include "DiscState.h"

void DiscState::initBackground()
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

void DiscState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/AppleGaramond.ttf"))
	{
		throw("ERROR:could not load font");
	}
}

void DiscState::initButtons()
{
	this->buttons["HELP"] = new Button(900, 750, 50, 50, &this->font, "Help", event);
	this->buttons["STEP"] = new Button(950, 750, 50, 50, &this->font, "Step", event);
	this->buttons["BACK"] = new Button(0, 750, 50, 50, &this->font, "Back", event);

	this->buttons["DRIVECONTENT"] = new Button(350, 100, 300, 100, &this->font, "Drive content", event);
	this->buttons["DISPLAYVECTOR"] = new Button(350, 250, 300, 100, &this->font, "Dispay vector", event);
	this->buttons["DISPLAYBLOCK"] = new Button(350, 400, 300, 100, &this->font, "Display block", event);
	this->buttons["DISPLAYCATALOQUE"] = new Button(350, 550, 300, 100, &this->font, "Display cataloque", event);
	this->buttons["DISPLAYOFT"] = new Button(350, 700, 300, 100, &this->font, "Display open files", event);
	this->buttons["QUEUE"] = new Button(650, 550, 300, 100, &this->font, "Display queue", event);
	
}

DiscState::DiscState(sf::RenderWindow *window, std::stack<State*> *states, sf::Event *event)
	:State(window, states, event)
{

	this->initFonts();
	this->initButtons();
	this->initBackground();
}

DiscState::~DiscState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second; //second poniewa¿ button* jest drugi w parze, pierwszy jest string
	}
}

void DiscState::endState()
{

}

void DiscState::updateKeybinds(const float& dt)
{
	this->checkForQuit();
}

void DiscState::update(const float& dt)
{
	if (event->type == sf::Event::MouseButtonReleased) {
		isMousePressed = false;
	}
	this->updateKeybinds(dt);
	this->updateMousePositions();
	this->updateTimebar();
	this->updateButtons();

}

void DiscState::updateButtons()
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

void DiscState::updateTimebar()
{
	this->timebar.getActualTime();
}

void DiscState::renderButtons(sf::RenderTarget * target)
{
	for (auto &it : this->buttons) {
		it.second->render(target);
	}
}

void DiscState::render(sf::RenderTarget* target)
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
