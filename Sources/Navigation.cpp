#include "../Headers/Navigation.h"


namespace Navigation {

	//================= MenuButton =================//
	// MenuButton
	MenuButton::MenuButton(const std::string& name, BUTTON_ID id)
		: id_(id)
	{
		text_.setFont(General::Fonts::MAIN);
		text_.setString(name);
		text_.setCharacterSize(24);
		text_.setFillColor(sf::Color::White);
	}

	// public
	void MenuButton::Draw(sf::RenderWindow& window) const {
		//std::cout << text_.getString().toUtf8().c_str() << std::endl;

		// выбивает ошибку 

		window.draw(text_);
	}

	void MenuButton::UpdatePosition(const sf::Vector2f& pos, float scale) {
		text_.setPosition(pos);
		text_.setScale(scale, scale);

	}

	void MenuButton::IsHover(const sf::Vector2f& pos) {
		if (text_.getGlobalBounds().contains(pos)) {
			text_.setFillColor(sf::Color::Yellow);
		}
		else {
			text_.setFillColor(sf::Color::White);
		}
	}

	BUTTON_ID MenuButton::IsClicked(const sf::Vector2f& pos) const {
		if (text_.getGlobalBounds().contains(pos))
			return id_;
		return BUTTON_ID::NONE;
	}






	//================= MainMenu =================//

	// constr & destr
	MainMenu::MainMenu() {
		Initialization();
	}


	// private
	void MainMenu::Initialization() {
		buttons_ = {
			MenuButton("Start / Stop", BUTTON_ID::START),
			MenuButton("Settings", BUTTON_ID::SETTINGS),
			MenuButton("Exit", BUTTON_ID::EXIT)
		};
	}

	void MainMenu::UpdateButtonsPosition(const sf::RenderWindow& window, float scale) {

		int i = 0;
		for (auto iter = buttons_.rbegin(); iter != buttons_. rend(); ++iter) {
			auto start_pos = window.mapPixelToCoords(
				{	0, 
					(int)General::HEIGHT - 30 - 30 * i++}
			);

			iter->UpdatePosition(start_pos, scale);
		}

	}


	// public
	void MainMenu::Draw(sf::RenderWindow& window) {
		for (const auto& btn : buttons_) {
			btn.Draw(window);
		}
	} 

	void MainMenu::Update(const sf::RenderWindow& window, float scale) {
		UpdateButtonsPosition(window, scale);
	}

	void MainMenu::IsHover(const sf::Vector2f& pos) {
		for (auto& btn : buttons_) {
			btn.IsHover(pos);
		}
	}

	void MainMenu::IsClicked(sf::RenderWindow& window, const sf::Vector2f& pos) const {
		for (const auto& btn : buttons_) {
			switch (btn.IsClicked(pos)) {
			case BUTTON_ID::START:

				break;
			case BUTTON_ID::SETTINGS:

				break;
			case BUTTON_ID::EXIT:
				window.close();
				break;
			}
		}
	}

}

