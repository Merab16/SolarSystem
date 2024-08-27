#pragma once
#include <SFML/Graphics.hpp>


namespace GeometricPrimitive {
	class FillRectangle: public sf::RectangleShape {
	private:
		


	private:



	public:
		FillRectangle(
			sf::Vector2f size = sf::Vector2f{20, 40},
			sf::Vector2f pos = sf::Vector2f{0, 0},
			sf::Color color = sf::Color::White
		);
		~FillRectangle();

	};

	class Rectangle : public sf::RectangleShape {
	private:



	private:



	public:
		Rectangle(
			sf::Vector2f size = sf::Vector2f{ 20, 40 },
			sf::Vector2f pos = sf::Vector2f{ 0, 0 },
			sf::Color color = sf::Color::Transparent
		);
		~Rectangle();

		void Update(const sf::Vector2f& pos, float scale);

	};


	class Ellipse : public sf::CircleShape {
	private:


	private:


	public:


	};
}

