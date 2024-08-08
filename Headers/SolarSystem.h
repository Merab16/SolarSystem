#pragma once
#include <SFML/Graphics.hpp>

namespace SolarSystem {

	class Planet {
	private:
		std::shared_ptr<sf::CircleShape> circle_;
		std::shared_ptr<sf::Sprite> sprite_;
		std::shared_ptr<sf::Texture> texture_;
		std::shared_ptr<sf::Image> image_;
		
		float angle_ = 0.f;
		float radius_ = 50.f;



	private:
		void Initialization();
		sf::Vector2f GetCenter(float w, float h);
		float AngleToRad(float angle);
		float RadToAngle(float rad);

	public:
		Planet();
		void Draw(sf::RenderWindow& window);
		void UpdatePosition(float dt);

	};


}