#pragma once
#include <SFML/Graphics.hpp>



#include "Cursor.h"
#include "Navigation.h"

namespace GUI {

	class Interface {
	private:
		float guiScale_;


		sf::Text& fps_;
		sf::Text& cursorPos_;

		// main menu
		Navigation::MainMenu mainMenu_;



	private:



	public:
		Interface(sf::Text& fps, sf::Text& cursor);
		void Draw(sf::RenderWindow& window);
		void Update(const sf::RenderWindow& window);
		void IsHover(const sf::Vector2f& pos);

		// getters
		float& GetScale() { return guiScale_; }




	};



}