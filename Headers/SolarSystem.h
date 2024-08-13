#pragma once
#include <SFML/Graphics.hpp>


#include "General.h"

namespace SolarSystem {

	class Planet {
	private:
		float ellipseA_, ellipseB_;

		float angle_ = 0.f;
		float radius_;
		float max_radius_;
		float min_radius_;
		float distance_;
		float velocity_ = 0.1f;
		float offsetAngle_;

		sf::Color color_;


	private:
		void Initialization();
		
		float AngleToRad(float angle);
		float RadToAngle(float rad);

		sf::Color RandomColor() const;

	protected:
		sf::Vector2f GetCenter(float w, float h, const sf::CircleShape& shape);
		std::unique_ptr<sf::CircleShape> circle_;
		std::unique_ptr<sf::Sprite> sprite_;
		std::unique_ptr<sf::Texture> texture_;
		std::unique_ptr<sf::Image> image_;
		std::unique_ptr<sf::CircleShape> ellipse_;

	public:
		Planet(float radius, float distance);
		void Draw(sf::RenderWindow& window) const;
		virtual void UpdatePosition(float dt);

		float GetAngle() const { return angle_ - offsetAngle_; }
		float GetDistance() const { return distance_; }
			

	};

	class Sun : public Planet {
	private:



	private:



	public:
		Sun(float radius);
		void UpdatePosition(float dt) override;
	};

}