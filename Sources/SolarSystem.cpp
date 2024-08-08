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
		circle_->setPosition(200.f, 200.f);

	}

	// public
	void Planet::Draw(sf::RenderWindow& window) {
		window.draw(*circle_);
	}

	void Planet::UpdatePosition(float dt) {

		//circle_->set


		circle_->setPosition(
			circle_->getPosition().x + sin(3.14159 * angle_ / 180),
			circle_->getPosition().y + 0.5 * cos(3.14159 * angle_ / 180)
		);

		
		if (angle_ >= 90 && angle_ < 270)
			radius_ -= sin(3.14159 / 180 * abs(angle_ - 180));
		else
			radius_ += sin(3.14159 / 180 * abs(angle_ - 180));

		angle_ += 50 * dt;

		if (angle_ > 360) angle_ -= 360;
		circle_->setRadius(radius_);
		std::cout << angle_ << std::endl;
	}
	

}
