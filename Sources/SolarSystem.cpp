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
	}


	// private
	void Planet::Initialization() {
		

		circle_ = std::make_unique<sf::CircleShape>();
		sprite_ = std::make_unique<sf::Sprite>();
		texture_ = std::make_unique<sf::Texture>();
		image_ = std::make_unique<sf::Image>();
		ellipse_ = std::make_unique<sf::CircleShape>();

		// texture 
		if (!texture_->loadFromFile("Images/" + name_ + ".png")) {
			std::cout << name_ + ".png can not find!" << std::endl;
		}
		texture_->setSmooth(true);

		// sprite
		sprite_->setTexture(*texture_);
		sprite_->setTextureRect(sf::IntRect(0, 0, General::SPRITE_SIZE, General::SPRITE_SIZE));
		sprite_->setScale(radius_ * 2 / General::SPRITE_SIZE, radius_ * 2 / General::SPRITE_SIZE);	



		max_radius_ = radius_;
		min_radius_ = 0.1 * radius_;


		circle_->setRadius(radius_);
		circle_->setPointCount(50);
		circle_->setFillColor(RandomColor());

		ellipse_->setRadius(1.4 * ellipseA_);
		ellipse_->setScale({ 1.f, 0.5f });
		ellipse_->setFillColor(sf::Color::Transparent);
		ellipse_->setOutlineThickness(0.1);
		ellipse_->setOutlineColor(sf::Color::Red);
		ellipse_->setPointCount(50);
		ellipse_->setPosition(
			General::WIDTH / 2 - ellipse_->getRadius(),
			General::HEIGHT / 2 - ellipse_->getRadius() / 2
		);

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
		//window.draw(*circle_);
		window.draw(*sprite_);

		sf::RectangleShape rect;
		rect.setSize(circle_->getGlobalBounds().getSize());
		rect.setPosition(circle_->getGlobalBounds().getPosition());
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::White);
		rect.setOutlineThickness(1);

		//window.draw(rect);
		
	}

	void Planet::DrawEllipse(sf::RenderWindow& window) const {
		window.draw(*ellipse_);
	}

	void Planet::UpdatePosition(float dt) {

		
		auto offset = GetCenter(General::WIDTH / 2, General::HEIGHT / 2, *circle_);
		// changing position via ellipse
		circle_->setPosition(
			offset.x + ((ellipseA_) * cos(AngleToRad(angle_)) + (ellipseA_) * sin(AngleToRad(angle_))),
			offset.y + ((-ellipseB_) * sin(AngleToRad(angle_)) + (ellipseB_) * cos(AngleToRad(angle_)))
		);
		sprite_->setPosition(
			offset.x + ((ellipseA_) * cos(AngleToRad(angle_)) + (ellipseA_) * sin(AngleToRad(angle_))),
			offset.y + ((-ellipseB_) * sin(AngleToRad(angle_)) + (ellipseB_) * cos(AngleToRad(angle_)))
		);
		  
		angle_ += (velocity_) * dt;
		if (angle_ > 360 + offsetAngle_) angle_ -= 360;

		auto delta = 0.00008 * velocity_ * (1 - abs(sin(AngleToRad((360) - (angle_ - offsetAngle_)))));
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

		
		UpdateSprite();
	}
	
	void Planet::UpdateSprite() {
		sprite_->setTextureRect(sf::IntRect(
			(spriteCounter_ / int(General::PERIOD_SCALE) % 30) * General::SPRITE_SIZE,
			(spriteCounter_ / int(General::PERIOD_SCALE) / 30) * General::SPRITE_SIZE,
			General::SPRITE_SIZE, General::SPRITE_SIZE));

		spriteCounter_++;
		if (spriteCounter_ == 60 * int(General::PERIOD_SCALE)) spriteCounter_ = 0;
	}


	// getters
	bool Planet::IsClicked(const sf::RenderWindow& window, sf::Vector2f pos) const {
		//sf::Transform tr = camera.getTransform();
		
		/*auto rect = camera.getViewport();
		auto x = camera.getCenter().x - camera.getSize().x / 2;
		auto y = camera.getCenter().y - camera.getSize().y / 2;
		std::cout << pos.x + rect.left << ' ' << pos.y + rect.top << std::endl;*/
		auto worldPos = window.mapPixelToCoords(static_cast<sf::Vector2i>(pos));
		return circle_->getGlobalBounds().contains(worldPos);
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
		sprite_->setPosition(offset);
	}

	// public



}
