#pragma once

#include "GeometicPrimitive.h"


namespace MyCursor {
	class Cursor {
	private:
		sf::Vector2i position_;
		sf::Text text_;
		sf::Font font_;

	private:
		void Initialization();
		void CreateText();

	public:
		Cursor();


		void UpdatePos(const sf::RenderWindow& window);
		void Draw(sf::RenderWindow& window);

	};
}