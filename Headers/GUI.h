#pragma once
#include <SFML/Graphics.hpp>
#include "Cursor.h"


namespace GUI {

	class Interface {
	private:
		// font
		sf::Font font_;

		float guiScale_;


		sf::Text& fps_;
		sf::Text& cursorPos_;





	private:



	public:
		Interface(sf::Text& fps, sf::Text& cursor);
		void Draw(sf::RenderWindow& window);
		void Update();
		float& GetScale() { return guiScale_; }




	};



}