#include <string>

#include "../Headers/Cursor.h"



namespace MyCursor {
	// constr && destr
	Cursor::Cursor() {
		Initialization();
	}

	// private
	void Cursor::Initialization() {
		font_.loadFromFile("Fonts/CascadiaCode.ttf");
		

		text_.setFont(font_);
		text_.setCharacterSize(16);
		//text_.setFillColor(sf::Color{ 150, 150, 150 });

		
	}

	// public
	void Cursor::UpdatePos(const sf::RenderWindow& window) {
		position_ = sf::Mouse::getPosition(window); 
		std::string pos = std::to_string(position_.x) + ';' + std::to_string(position_.y);
		text_.setString(pos);
		text_.setPosition(sf::Vector2f{(float)position_.x + 20, (float)position_.y});
	}

	void Cursor::Draw(sf::RenderWindow& window) {
		window.draw(text_);
	}

}
