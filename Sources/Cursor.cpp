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
		font_.loadFromFile("Fonts/CascadiaCode.ttf");
		

		text_.setFont(font_);
		text_.setCharacterSize(16);
		text_.setFillColor(sf::Color{ 90, 160, 190 });

		
	}




	// public
	void Cursor::UpdatePos(const sf::RenderWindow& window, sf::Vector2f cameraOffset) {
		position_ = sf::Mouse::getPosition(window); 
		std::string pos = std::to_string(position_.x) + ';' + std::to_string(position_.y);
		text_.setString(pos);
		text_.setPosition(sf::Vector2f{
			(float)position_.x + 20 + (cameraOffset.x - General::WIDTH / 2),
			(float)position_.y + (cameraOffset.y - General::HEIGHT / 2)
		});
	}

	void Cursor::Draw(sf::RenderWindow& window) {
		window.draw(text_);
	}

}
