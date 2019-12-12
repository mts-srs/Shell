#include "CreateProcessInput.h"

void CreateProcessInput::initBackground()
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

void CreateProcessInput::initFonts()
{
	if (!this->font.loadFromFile("Fonts/AppleGaramond.ttf"))
	{
		throw("ERROR:could not load font");
	}
}

void CreateProcessInput::initButtons()
{
	this->buttons["STEP"] = new Button(950, 750, 50, 50, &this->font, "Step", event);
	this->buttons["BACK"] = new Button(0, 750, 50, 50, &this->font, "Back", event);
}

CreateProcessInput::CreateProcessInput(sf::RenderWindow *window, std::stack<State*> *states, sf::Event *event)
	:State(window, states, event)
{

	this->initFonts();
	this->initButtons();
	this->initBackground();

}

CreateProcessInput::~CreateProcessInput()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

void CreateProcessInput::endState()
{

}

void CreateProcessInput::updateKeybinds(const float& dt)
{
	this->checkForQuit();
}

void CreateProcessInput::update(const float& dt)
{
	if (event->type == sf::Event::MouseButtonReleased) {
		isMousePressed = false;
	}
	this->updateKeybinds(dt);
	this->updateMousePositions();
	this->updateTimebar();
	this->updateButtons();
	if(input.keycounter < 3) {
		this->updateInput();
	}
	else {
		for (auto e : input.vec) {
			std::cout << e << std::endl;
		}
		std::cout << input.vec.size();
		this->states->pop();
	}
}

void CreateProcessInput::updateButtons()
{
	//updating buttons and does all funcionality
	for (auto &it : this->buttons) {
		it.second->update(this->mousePosView);
	}

	//Quiting shell
	if (this->buttons["BACK"]->isPressed() && isMousePressed == false) {
		isMousePressed = true;
		this->states->pop();
	}
}

void CreateProcessInput::updateTimebar()
{
	this->timebar.getActualTime();
}

void CreateProcessInput::updateInput()
{
	this->input.update();
}

void CreateProcessInput::renderButtons(sf::RenderTarget * target)
{
	for (auto &it : this->buttons) {
		it.second->render(target);
	}
}

void CreateProcessInput::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}

	target->draw(this->background);
	this->renderButtons(target);
	this->timebar.render(target);
	this->input.render(target);
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
