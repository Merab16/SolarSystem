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
	void Cursor::UpdatePos(const sf::RenderWindow& window, const sf::View& camera, sf::Vector2f cameraOffset) {
		position_ = sf::Mouse::getPosition(window); 
		
		std::string pos = std::to_string(position_.x) + ';' + std::to_string(position_.y);
		text_.setString(pos);
		text_.setPosition(sf::Vector2f{
			 (cameraOffset.x - camera.getSize().x / 2 ),
			 20 + (cameraOffset.y - camera.getSize().y / 2 )
		});
	}

	void Cursor::Draw(sf::RenderWindow& window) {
		window.draw(text_);
	}

}
