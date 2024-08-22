#include <string>

#include "../Headers/Cursor.h"
#include "../Headers/General.h"


namespace MyCursor {
	// constr && destr
	Cursor::Cursor() {
		Initialization();
	}

	// private
	void Cursor::Initialization() {
		text_.setFont(General::Fonts::MAIN_FONT);
		text_.setCharacterSize(16);
		text_.setFillColor(sf::Color{ 90, 160, 190 });

		
	}




	// public
	void Cursor::UpdatePos(const sf::RenderWindow& window, const sf::Vector2f& pos) {
		position_ = sf::Mouse::getPosition(window); 
		
		std::string posText = std::to_string(position_.x) + ';' + std::to_string(position_.y);
		text_.setString(posText);
		text_.setPosition(sf::Vector2f{ pos.x, pos.y });
	}

	void Cursor::SetScale(float scale) {
		text_.setScale(scale, scale);
	}

}
