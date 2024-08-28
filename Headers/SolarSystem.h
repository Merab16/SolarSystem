#pragma once
#include <SFML/Graphics.hpp>


#include "General.h"

namespace SolarSystem {

	class Planet {
	private:

		// data
		General::PlanetInfo info_;

		// scales
		float distanceScale_ = 100;

		// sprite rotation
		size_t spriteCounter_ = 0;



		float ellipseA_, ellipseB_;

		float angle_ = 0.f;
		float max_radius_;
		float min_radius_;
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
		Planet(const General::PlanetInfo& info);
		void Draw(sf::RenderWindow& window) const;
		void DrawEllipse(sf::RenderWindow& window) const;
		virtual void UpdatePosition(float dt);
		void UpdateSprite();

		// getters
		float GetAngle() const { return angle_ - offsetAngle_; }
		float GetDistance() const { return info_.distance; }
		bool IsClicked(const sf::RenderWindow& window, sf::Vector2f pos) const;
		const std::string& GetName() const { return info_.name; }
		float GetRadius() const { return info_.radius;  }
		const General::PlanetInfo& GetInfo() const { return info_; }
	};

	class Sun : public Planet {
	private:



	private:



	public:
		Sun(float radius);
		void UpdatePosition(float dt) override;
	};

}