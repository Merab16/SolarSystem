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

	public:
		Cursor();


		void UpdatePos(const sf::RenderWindow& window, const sf::Vector2f& pos);
		void Draw(sf::RenderWindow& window);
		void SetScale(float scale);

		// getters
		sf::Vector2f GetPosition() const { return static_cast<sf::Vector2f>(position_); };
	};
}