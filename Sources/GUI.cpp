#include "../Headers/GUI.h"




namespace GUI {
	// constr & destr
	Interface::Interface(sf::Text& fps, sf::Text& cursor)
		: guiScale_(1.f)
		, fps_(fps)
		, cursorPos_(cursor)
	{

	}


	// public
	void Interface::Draw(sf::RenderWindow& window) {
		mainMenu_.Draw(window);

		window.draw(fps_);
		window.draw(cursorPos_);

	}

	void Interface::Update(const sf::RenderWindow& window) {
		fps_.setScale(guiScale_, guiScale_);
		cursorPos_.setScale(guiScale_, guiScale_);
		
		mainMenu_.Update(window, guiScale_);
	}

	void Interface::IsHover(const sf::Vector2f& pos) {
		mainMenu_.IsHover(pos);
	}


}