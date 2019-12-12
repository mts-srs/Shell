#include "FileManagerState.h"

void FileManagerState::initBackground()
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

void FileManagerState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/AppleGaramond.ttf"))
	{
		throw("ERROR:could not load font");
	}
}

void FileManagerState::initButtons()
{
	this->buttons["HELP"] = new Button(900, 750, 50, 50, &this->font, "Help", event);
	this->buttons["STEP"] = new Button(950, 750, 50, 50, &this->font, "Step", event);
	this->buttons["BACK"] = new Button(0, 750, 50, 50, &this->font, "Back", event);
	
	this->buttons["CREATE_FILE"] = new Button(350, 100, 300, 100, &this->font, "Create file", event);
	this->buttons["DELETE_FILE"] = new Button(350, 250, 300, 100, &this->font, "Delete file", event);
	this->buttons["RENAME_FILE"] = new Button(350, 400, 300, 100, &this->font, "Rename file", event);
	this->buttons["WRITE_TO_FILE"] = new Button(350, 550, 300, 100, &this->font, "Write to file", event);
	this->buttons["OVERWRITE_FILE"] = new Button(350, 700, 300, 100, &this->font, "Overwrite file", event);
}

FileManagerState::FileManagerState(sf::RenderWindow *window, std::stack<State*> *states, sf::Event *event)
	:State(window, states, event)
{
	this->initFonts();
	this->initButtons();
	this->initBackground();
}

FileManagerState::~FileManagerState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

void FileManagerState::endState()
{

}

void FileManagerState::updateKeybinds(const float& dt)
{
	this->checkForQuit();
}

void FileManagerState::update(const float& dt)
{
	if (event->type == sf::Event::MouseButtonReleased) {
		isMousePressed = false;
	}
	this->updateKeybinds(dt);
	this->updateMousePositions();
	this->updateTimebar();
	this->updateButtons();
}

void FileManagerState::updateButtons()
{
	//updating buttons and does all funcionality
	for (auto &it : this->buttons) {
		it.second->update(this->mousePosView);
	}

	if (this->buttons["CREATE_FILE"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->push(new CreateFileInput(this->window, this->states, this->event));
	}

	if (this->buttons["DELETE_FILE"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->push(new DeleteFileInput(this->window, this->states, this->event));
	}

	if (this->buttons["RENAME_FILE"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->push(new RenameFileInput(this->window, this->states, this->event));
	}

	if (this->buttons["WRITE_TO_FILE"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->push(new WriteFileInput(this->window, this->states, this->event));
	}

	if (this->buttons["OVERWRITE_FILE"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->push(new OverwriteFileInput(this->window, this->states, this->event));
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

void FileManagerState::updateTimebar()
{
	this->timebar.getActualTime();
}

void FileManagerState::renderButtons(sf::RenderTarget * target)
{
	for (auto &it : this->buttons) {
		it.second->render(target);
	}
}

void FileManagerState::render(sf::RenderTarget* target)
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
