#include <cmath>
#include <iostream>


#include "../Headers/SolarSystem.h"


namespace SolarSystem {

	Planet::Planet(float radius, float distance)
		: radius_(radius)
		, distance_(distance)
		, ellipseA_(2 * distance)
		, ellipseB_(distance)
		, velocity_(radius * 0.1)
	{
		Initialization();
		angle_ = 45; 
		offsetAngle_ = 45;
		//RadToAngle(atan(ellipseB_ / ellipseA_));
	}


	// private
	void Planet::Initialization() {

		circle_ = std::make_unique<sf::CircleShape>();
		sprite_ = std::make_unique<sf::Sprite>();
		texture_ = std::make_unique<sf::Texture>();
		image_ = std::make_unique<sf::Image>();
		ellipse_ = std::make_unique<sf::CircleShape>();

		max_radius_ = radius_;
		min_radius_ = 0.1 * radius_;

		
		/*ellipse_->setFillColor(sf::Color::Transparent);
		ellipse_->setOutlineThickness(2);
		ellipse_->setOutlineColor(sf::Color::Green);
		ellipse_->setRadius(ellipse_a);
		ellipse_->setScale(1.5, 1);
		ellipse_->setPosition({400 - 3 * ellipse_a / 2, 300 - ellipse_b / 2});*/

		circle_->setRadius(radius_);
		circle_->setPointCount(50);

	}

	sf::Vector2f Planet::GetCenter(float w, float h, const sf::CircleShape& shape) {
		return { w - shape.getRadius(), h - shape.getRadius() };
	}

	float Planet::AngleToRad(float angle) {
		return 3.14159 / 180 * angle;
	}

	float Planet::RadToAngle(float rad) {
		return rad * 180 / 3.14159;
	}

	// public
	void Planet::Draw(sf::RenderWindow& window) const {
		window.draw(*ellipse_);
		window.draw(*circle_);
		
	}

	void Planet::UpdatePosition(float dt) {

		
		auto offset = GetCenter(General::WIDTH / 2, General::HEIGHT / 2, *circle_);
		//auto res = RadToAngle(atan(ellipseB_ / ellipseA_));
		// changing position via ellipse
		circle_->setPosition(
			offset.x + ((ellipseA_) * cos(AngleToRad(angle_)) + (ellipseA_) * sin(AngleToRad(angle_))),
			offset.y + ((-ellipseB_) * sin(AngleToRad(angle_)) + (ellipseB_) * cos(AngleToRad(angle_)))
		);
		  
		angle_ += (velocity_ * dt);
		if (angle_ > 360 + offsetAngle_) angle_ -= 360;

		//std::cout << dt << std::endl;
		

		//auto delta = 0.04 * abs(cos(AngleToRad((360 + res) - angle_ ))) * 0.01 * ((3.14159 * radius_) / velocity_);

		auto delta = 0.005 * velocity_ * (1 - abs(sin(AngleToRad((360) - (angle_ - offsetAngle_)))));
		std::cout << angle_ - offsetAngle_ << std::endl;

		if (angle_  > 270 + offsetAngle_ || angle_ <= 90 + offsetAngle_) {
 			if (radius_ > min_radius_)
				radius_ -= delta;
		}
		else {
			if (radius_ < max_radius_)
				radius_ += delta;
		}
		 
		circle_->setRadius(radius_);
		
	}
	

}
