#include "../Headers/General.h"

#include <iostream>

namespace General {
	
	// Fonts
	sf::Font Fonts::MAIN_FONT;
	void Fonts::Initialization() {
		MAIN_FONT.loadFromFile("Fonts/CascadiaCode.ttf");
	}

}
