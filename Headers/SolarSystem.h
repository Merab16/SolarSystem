#pragma once
#include <SFML/Graphics.hpp>


#include "General.h"

namespace SolarSystem {

	class Planet {
	private:
		std::unique_ptr<sf::CircleShape> circle_;
		std::unique_ptr<sf::Sprite> sprite_;
		std::unique_ptr<sf::Texture> texture_;
		std::unique_ptr<sf::Image> image_;
		std::unique_ptr<sf::CircleShape> ellipse_;
		
		float ellipseA_, ellipseB_;

		float angle_ = 0.f;
		float radius_;
		float max_radius_;
		float min_radius_;
		float distance_;
		float velocity_ = 0.1f;
		float offsetAngle_;




	private:
		void Initialization();
		sf::Vector2f GetCenter(float w, float h, const sf::CircleShape& shape);
		float AngleToRad(float angle);
		float RadToAngle(float rad);

	public:
		Planet(float radius, float distance);
		void Draw(sf::RenderWindow& window) const;
		void UpdatePosition(float dt);

	};


}