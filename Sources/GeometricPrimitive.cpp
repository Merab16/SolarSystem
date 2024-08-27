#include "../Headers/GeometicPrimitive.h"	

namespace GeometricPrimitive {

	//================= FillRectangle =================//

	// constr && destr
	FillRectangle::FillRectangle(sf::Vector2f size, sf::Vector2f pos, sf::Color color)
	: sf::RectangleShape(size)
	{
		setPosition(pos);
		setFillColor(color);
	}

	FillRectangle::~FillRectangle() {

	}

	// private

	// public


	//================= Rectangle =================//
	// constr && destr
	Rectangle::Rectangle(sf::Vector2f size, sf::Vector2f pos, sf::Color color)
		: sf::RectangleShape(size)
	{
		setPosition(pos);
		setFillColor(sf::Color::Transparent);
		setOutlineThickness(1.f);
		setOutlineColor(color);
	}

	Rectangle::~Rectangle() {

	}

	// private

	// public
	void Rectangle::Update(const sf::Vector2f& pos, float scale) {
		setPosition(pos);
		setScale(scale, scale);
	}
}
