#include <cmath>
#include <iostream>


#include "../Headers/SolarSystem.h"


namespace SolarSystem {

	Planet::Planet() {
		Initialization();
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
	void Planet::Draw(sf::RenderWindow& window) {
		window.draw(*ellipse_);
		window.draw(*circle_);
		
	}

	void Planet::UpdatePosition(float dt) {

		//circle_->set
		auto offset = GetCenter(400, 300, *circle_);
		//circle_->setPosition(offset);
		circle_->setPosition(
			offset.x + ((ellipse_a) * cos(AngleToRad(angle_)) + (ellipse_a) * sin(AngleToRad(angle_))),
			offset.y + ((-ellipse_b) * sin(AngleToRad(angle_)) + (ellipse_b) * cos(AngleToRad(angle_)))
		);
		float dt_scale = 20;
		angle_ += dt_scale * dt;
		if (angle_ > 360) angle_ -= 360;
		auto res = RadToAngle(atan(ellipse_b / ellipse_a));

		auto delta = 0.04 * abs(cos(AngleToRad((360 + res) - angle_ )));
		//std::cout << angle_ - res << std::endl;
		//std::cout << delta << std::endl;
		//std::cout << radius_ << std::endl;
		if (angle_ > 270 + res || angle_ <= 90 + res) {
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
