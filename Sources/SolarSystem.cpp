#include <cmath>
#include <iostream>
#include <random>


#include "../Headers/SolarSystem.h"

// https://wika.tutoronline.ru/fizika/class/11/solnechnaya-sistema
// PLANETS	dist	D, km	
// sun		
// mercury	0.39	4.9k
// venus	0.72	12.1k
// earth	1.		12.7k
// mars		1.52	6.8k
// jupiter	5.2		139.8k
// saturn	9.54	116k
// uranus	19.19	50.8k
// neptune	30.07	48.6k



namespace SolarSystem {

	Planet::Planet(const std::string& name, float distance, float period,
		float diametr, float weight, float velocity)
		: name_(name)
		, distance_(distance)
		, sunPeriod_(period)
		, radius_(diametr / 2)
		, weight_(weight)
		, velocity_(velocity)
		, ellipseA_(2 * distance)
		, ellipseB_(distance)
		//, velocity_(radius * 0.01)
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


		circle_->setRadius(radius_);
		circle_->setPointCount(50);
		circle_->setFillColor(RandomColor());

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

	sf::Color Planet::RandomColor() const {
		std::random_device rd;
		std::mt19937 mersenne(rd());
		return sf::Color(mersenne() % 255, mersenne() % 255, mersenne() % 255);
	}

	// public
	void Planet::Draw(sf::RenderWindow& window) const {
		//window.draw(*ellipse_);
		window.draw(*circle_);
		
	}

	void Planet::UpdatePosition(float dt) {

		
		auto offset = GetCenter(General::WIDTH / 2, General::HEIGHT / 2, *circle_);
		
		// changing position via ellipse
		circle_->setPosition(
			offset.x + ((ellipseA_) * cos(AngleToRad(angle_)) + (ellipseA_) * sin(AngleToRad(angle_))),
			offset.y + ((-ellipseB_) * sin(AngleToRad(angle_)) + (ellipseB_) * cos(AngleToRad(angle_)))
		);
		  
		angle_ += (velocity_) * dt;
		if (angle_ > 360 + offsetAngle_) angle_ -= 360;

		auto delta = 0.00005 * velocity_ * (1 - abs(sin(AngleToRad((360) - (angle_ - offsetAngle_)))));
		//std::cout << angle_ - offsetAngle_ << std::endl;

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
	

	//===SUN===//

	// constr & destr
	Sun::Sun(float radius)
		: Planet("Sun", 0, 0, 2 * radius, 0, 0)
	{
		circle_->setFillColor(sf::Color(200, 210, 21));
	}


	// private
	void Sun::UpdatePosition(float dt) {
		auto offset = GetCenter(General::WIDTH / 2, General::HEIGHT / 2, *circle_);
		circle_->setPosition(offset.x, offset.y);
		
	}

	// public



}
