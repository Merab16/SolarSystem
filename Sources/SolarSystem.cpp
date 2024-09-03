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


// sun
// ffee00
// f6a10c
// 777431
// fffacd
// e8cd1b
// ff4500
// f5f5f5



namespace SolarSystem {
	using namespace General;


	Planet::Planet(const General::PlanetInfo& info)
		: info_(info)
		, ellipseA_(2 * (info.distance + 60))
		, ellipseB_(info.distance + 60)
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
		if (!texture_->loadFromFile("Images/" + info_.name + ".png")) {
			std::cout << info_.name + ".png can not find!" << std::endl;
		}
		texture_->setSmooth(true);

		// sprite
		sprite_->setTexture(*texture_);
		sprite_->setTextureRect(sf::IntRect(0, 0, (int)General::SPRITE_SIZE, (int)General::SPRITE_SIZE));
		sprite_->setScale((info_.radius) * 2 / (int)General::SPRITE_SIZE, (info_.radius) * 2 / (int)General::SPRITE_SIZE);



		max_radius_ = (info_.radius);
		min_radius_ = 0.1f * (info_.radius);


		circle_->setRadius((info_.radius));
		circle_->setPointCount(50);
		circle_->setFillColor(RandomColor());

		ellipse_->setRadius(1.4f * ellipseA_);
		ellipse_->setScale({ 1.f, 0.5f });
		ellipse_->setFillColor(sf::Color::Transparent);
		ellipse_->setOutlineThickness(0.1f);
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
		return 3.14159f / 180 * angle;
	}

	float Planet::RadToAngle(float rad) {
		return rad * 180 / 3.14159f;
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
		  
		angle_ += (info_.velocity) * dt;
		if (angle_ > 360 + offsetAngle_) angle_ -= 360;

		float delta = 0.00008f * info_.velocity * (1 - abs(sin(AngleToRad((360) - (angle_ - offsetAngle_)))));
		//std::cout << angle_ - offsetAngle_ << std::endl;

		if (angle_  > 270 + offsetAngle_ || angle_ <= 90 + offsetAngle_) {
 			if (info_.radius > min_radius_)
				info_.radius -= delta;
		}
		else {
			if (info_.radius < max_radius_)
				info_.radius += delta;
		}
		 
		circle_->setRadius(info_.radius);

		
		UpdateSprite();
	}
	
	void Planet::UpdateSprite() {
		sprite_->setTextureRect(sf::IntRect(
			((int)spriteCounter_ / SCALE_ROTATION % SPRITE_WIDTH) * (int)SPRITE_SIZE,
			((int)spriteCounter_ / SCALE_ROTATION / SPRITE_WIDTH) * (int)SPRITE_SIZE,
			(int)SPRITE_SIZE, (int)SPRITE_SIZE));

		spriteCounter_++;
		if (spriteCounter_ >= SPRITE_WIDTH * SPRITE_HEIGHT * SCALE_ROTATION) spriteCounter_ = 0;
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
		: Planet({ "Sun", 0, 0, 2 * radius, 0, 0 })
	{
		//circle_->setFillColor(sf::Color(200, 210, 21));
		Initialization();
	}


	// private

	void Sun::Initialization() {
		sprite_ = std::make_unique<sf::Sprite>();
		texture_ = std::make_unique<sf::Texture>();


		// texture 
		if (!texture_->loadFromFile("Images/" + info_.name + ".png")) {
			std::cout << info_.name + ".png can not find!" << std::endl;
		}
		texture_->setSmooth(true);

		// sprite
		sprite_->setTexture(*texture_);
		sprite_->setTextureRect(sf::IntRect(0, 0, (int)SUN_SPRITE_SIZE, (int)SUN_SPRITE_SIZE));
		sprite_->setScale((info_.radius) * 2 / (int)SUN_SPRITE_SIZE, (info_.radius) * 2 / (int)SUN_SPRITE_SIZE);

	}

	void Sun::UpdateSprite() {



		sprite_->setTextureRect(sf::IntRect(
			int(spriteCounter_ / SUN_SCALE_ROTATION) % SUN_SPRITE_WIDTH * SUN_SPRITE_SIZE,
			int(spriteCounter_ / SUN_SCALE_ROTATION) / SUN_SPRITE_WIDTH * SUN_SPRITE_SIZE,
			(int)SUN_SPRITE_SIZE, (int)SUN_SPRITE_SIZE
		));

		spriteCounter_++;
		if (spriteCounter_ >= SUN_SPRITE_WIDTH * SUN_SPRITE_HEIGHT * SUN_SCALE_ROTATION) spriteCounter_ = 0;
	}

	// public
	void Sun::UpdatePosition(float dt) {
		sf::Vector2f offset = { 
			WIDTH / 2 - (SUN_SPRITE_SIZE / 2 * sprite_->getScale().x), 
			HEIGHT / 2 - (SUN_SPRITE_SIZE / 2 * sprite_->getScale().y) };
		sprite_->setPosition(offset); 
		UpdateSprite();
	}

	// getters
	sf::Vector2f Planet::GetCentre() const {
		return { sprite_->getPosition().x + (SPRITE_SIZE / 2) * sprite_->getScale().x,
			sprite_->getPosition().y + (SPRITE_SIZE / 2) * sprite_->getScale().y};
	}
}
