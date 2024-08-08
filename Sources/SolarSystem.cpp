#include <cmath>
#include <iostream>


#include "../Headers/SolarSystem.h"


namespace SolarSystem {

	Planet::Planet() {
		Initialization();
	}


	// private
	void Planet::Initialization() {

		circle_ = std::make_shared<sf::CircleShape>();
		sprite_ = std::make_shared<sf::Sprite>();
		texture_ = std::make_shared<sf::Texture>();
		image_ = std::make_shared<sf::Image>();



		circle_->setRadius(radius_);
		circle_->setPointCount(50);

	}

	sf::Vector2f Planet::GetCenter(float w, float h) {
		return { w - circle_->getRadius(), h - circle_->getRadius() };
	}

	float Planet::AngleToRad(float angle) {
		return 3.14159 / 180 * angle;
	}

	float Planet::RadToAngle(float rad) {
		return rad * 180 / 3.14159;
	}

	// public
	void Planet::Draw(sf::RenderWindow& window) {
		window.draw(*circle_);
	}

	void Planet::UpdatePosition(float dt) {

		//circle_->set
		auto offset = GetCenter(400, 300);
		float elipse_a = 200, elipse_b = 100;
		//circle_->setPosition(offset);
		circle_->setPosition(
			offset.x + ((elipse_a) * cos(AngleToRad(angle_)) + (elipse_a) * sin(AngleToRad(angle_))),
			offset.y + ((-elipse_b) * sin(AngleToRad(angle_)) + (elipse_b) * cos(AngleToRad(angle_)))
		);
		float dt_scale = 20;
		angle_ += dt_scale * dt;
		if (angle_ > 360) angle_ -= 360;
		auto res = RadToAngle(atan(elipse_b / elipse_a));
		
		if (angle_ > 270 + res || angle_ <= 90 + res) {
			auto delta = (dt_scale * 0.2) / 50 * sin(AngleToRad(abs(90 - abs(angle_ - 180))));
			radius_ -= delta;
			
		}
		else {
			auto delta = (dt_scale * 0.15) / 50 * sin(AngleToRad(abs(90 - abs(angle_ - 180))));
			radius_ += delta;
			
		}
		

		circle_->setRadius(radius_);
		
	}
	

}
