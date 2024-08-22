#include "../Headers/GUI.h"




namespace GUI {
	// constr & destr
	Interface::Interface(sf::Text& fps, sf::Text& cursor)
		: guiScale_(1.f)
		, fps_(fps)
		, cursorPos_(cursor)
	{
		font_.loadFromFile("Fonts/CascadiaCode.ttf");

	}


	// public
	void Interface::Draw(sf::RenderWindow& window) {
		window.draw(fps_);
		window.draw(cursorPos_);
	}

	void Interface::Update() {
		fps_.setScale(guiScale_, guiScale_);
		cursorPos_.setScale(guiScale_, guiScale_);
		
	}



}