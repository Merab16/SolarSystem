#pragma once
#include <SFML/Graphics.hpp>

namespace SolarSystem {

	class Planet {
	private:
		std::unique_ptr<sf::CircleShape> circle_;
		std::unique_ptr<sf::Sprite> sprite_;
		std::unique_ptr<sf::Texture> texture_;
		std::unique_ptr<sf::Image> image_;
		std::unique_ptr<sf::CircleShape> ellipse_;
		
		float ellipse_a = 200, ellipse_b = 100;

		float angle_ = 0.f;
		float radius_ = 50.f;
		float max_radius_;
		float min_radius_;
		float deltaSpeed_ = 0.1f;




	private:
		void Initialization();
		sf::Vector2f GetCenter(float w, float h, const sf::CircleShape& shape);
		float AngleToRad(float angle);
		float RadToAngle(float rad);

	public:
		Planet();
		void Draw(sf::RenderWindow& window);
		void UpdatePosition(float dt);

	};


}