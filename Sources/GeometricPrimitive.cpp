#include "../Headers/GeometicPrimitive.h"	

namespace GeometricPrimitive {

	// constr && destr
	Rectangle::Rectangle(sf::Vector2f size, sf::Vector2f pos, sf::Color color)
	: sf::RectangleShape(size)
	{
		setPosition(pos);
		setFillColor(color);
		setOutlineThickness(1.f);
		setOutlineColor(sf::Color(255, 255, 255));
	}

	Rectangle::~Rectangle() {

	}

	// private

	// public



}
