#include "../Headers/General.h"

#include <iostream>

namespace General {
	
	// Fonts
	sf::Font Fonts::MAIN;
	sf::Font Fonts::DEFAULT;
	void Fonts::Initialization() {
		DEFAULT.loadFromFile("Fonts/CascadiaCode.ttf");
		MAIN.loadFromFile("Fonts/Audiowide.ttf");
	}

	// convert current pos to global
	sf::Vector2f CurrentToGlobalPos(const sf::RenderWindow& window, const sf::Vector2f& pos) {
		return window.mapPixelToCoords(static_cast<sf::Vector2i>(pos));
	}

}
